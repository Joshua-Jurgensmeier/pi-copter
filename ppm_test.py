#!!!!!!!!! DID YOU FORGET TO START THE PIGPIO PROCESS?!!!!!!!!!

#Created using https://github.com/jsa/flystick.git for reference

from time import sleep
from pigpio import *

OUTPUT_PIN = 18

pin_mask = 1 << 18

pi = pigpio.pi()

pi.setmode(OUTPUT_PIN, pigpio.OUTPUT)

pi.wave_clear()

waves = []

"""
channels
 1 : Throttle
 2 : Roll
 3 : Pitch
 4 : Yaw
 5 : FlightMode
 6 : Collective
 7 : Accessory0
 8 : Accessory1


  700-1,700 pulse                        3,700 (at least) pulse between frames
      v                8 channels                       v
     ___   ___   ___   ___   ___   ___   ___   ___   ________
   _| 1 |_| 2 |_| 3 |_| 4 |_| 5 |_| 6 |_| 7 |_| 8 |_|  end   |
   ^
  300 delay   |_____|
                 v
            2,000 channel
|_______________________________________________________________|
                            v
                       20,000 frame


9 * 300 + 8 * 1,700 + 3,700 = 20,000
"""

delay = 300

num_channels = 8

"""
 If all channels are at max (1,700) then the pulse between frames is 3,700.  If all channels are
 at minimum (700) then the pulse between frames increases by 8,000 (1,000 for each frame)
 to 11,700 in order to make up the difference and keep the frame size at 20,000
"""
end_pulse_max = 11700

# Generates 3 wave in which all eight channels recieve 1000, 1500, 2000 microsecond pulses
# respectively (including 300 microsecond delay)
for wave in range(3):
    pulse_length = [1000, 1500, 2000]

    pulses = []

    # for calculating delay between frames
    total_pulse_length = pulse_length[wave] * 8

    for channel in range(8):
        # 300 delay
        pulses += pulse(0, pin_mask, delay)

        # 700-1,700 pulse
        pulses += pulse(pin_mask, 0, pulse_length[wave] - delay)

    # 9th 300 delay
    pulses += pulse(0, pin_mask, delay)

    # 3,700 (at least) pulse between frames
    pulses += pulse(pin_mask, 0, end_pulse_max - total_pulse_length)

    pi.wave_add_generic(pulses)

    waves[wave] = pi.wave_create()

for wave in waves:
    pi.wave_send_repeat(wave)

    sleep(5)
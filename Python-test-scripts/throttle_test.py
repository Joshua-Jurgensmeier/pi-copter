#!!!!!!!!! DID YOU FORGET TO START THE PIGPIO PROCESS?!!!!!!!!!

# 'us' stands for microseconds.  Sorry, I ain't got no mu
# Rev throttle and hold all other channels at neutral

#Created using https://github.com/jsa/flystick.git for reference

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

All times in microseconds.

 6,200 (at least) sync pulse between frames         700-1,700 value pulse                        
        v                 8 channels                      v
    ________   ___   ___   ___   ___   ___   ___   ___   ___  
   |  sync  |_| 1 |_| 2 |_| 3 |_| 4 |_| 5 |_| 6 |_| 7 |_| 8 |_
             ^
          300 delay                   |_____|
                                         v
                          channels (value + delay) 1,000 - 2,000
|_______________________________________________________________|
                            v
                       22,500 frame
"""

from time import sleep
from pigpio import *


#init pigpio object and ppm variables
OUTPUT_PIN = 24
pin_mask = 1 << OUTPUT_PIN
pi = pi()
pi.set_mode(OUTPUT_PIN, OUTPUT)
pi.wave_clear()
delay_us = 300
num_channels = 8
frame_size_us = 22500
channel_vals_us = [1700, 1200, 1200, 1200, 1200, 1200, 1200, 1200]
total_length_us = 0
pulses = []


#assemble frame
for channel in range(num_channels):
    
    #add the length of value and delay pulses to total_length for calculating sync pulse
    total_length_us += delay_us + channel_vals_us[channel]

    #add delay
    pulses += [pulse(0, pin_mask, delay_us)]
    
    #add channel
    pulses += [pulse(pin_mask, 0, channel_vals_us[channel])]

#add last (9th) delay
total_length += delay_us
pulses += [pulse(0, pin_mask, delay_us)]

#add sync pulse at beginning of frame
pulses.insert(0, pulse(pin_mask, 0, frame_size_us - total_length_us))

#create frame from data
pi.wave_add_generic(pulses)    
newWave = pi.wave_create() 
pi.wave_send_using_mode(newWave, WAVE_MODE_REPEAT_SYNC)


input("Enter to continue")

#turn it all off
pi.wave_delete(newWave)
#Bring pin low... FOREVER
pi.wave_add_generic([pulse(0, pin_mask, 1000)])
pi.wave_send_using_mode(pi.wave_create(), WAVE_MODE_REPEAT_SYNC)
pi.stop()

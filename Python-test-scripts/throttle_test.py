# 'us' stands for microseconds.  Sorry, I ain't got no mu
#Rev throttle and hold all other channels at neutral

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
channel_vals_us = [1875, 1500, 1500, 1500, 1500, 1500, 1500, 1500]
total_length_us = 0
pulses = []


#assemble frame
for channel in range(num_channels):
    
    #add the length of both pulses to total_length for calculating sync pulse
    total_length_us += delay_us + channel_vals_us[channel]

    #add delay
    pulses += [pulse(0, pin_mask, delay_us)]
    #add channel
    pulses += [pulse(pin_mask, 0, channel_vals_us[channel])]

#add last delay
pulses += [pulse(0, pin_mask, delay_us)]

#add sync pulse at beginning of frame
pulses.insert(0, pulse(pin_mask, 0, frame_size - total_length - delay))

#generate frame

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
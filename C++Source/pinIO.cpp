#include "pinIO.hpp"

void PinIO::sendPPM(std::map<char, int> &channels)
{

	/*

	channels
	1 | Throttle   |  t
	2 | Roll       |  r
	3 | Pitch	   |  p
	4 | Yaw		   |  y
	5 | FlightMode |  m <- for backflips?
	6 | Collective |  c	<- probably not used...
	7 | Accessory0 |  0	<- for like arming
	8 | Accessory1 |  1	<- more backflips?

	*/

	//Array of channels' keys in correct channel order for building ppm wave.
	char channelKeys[] = { 't', 'r', 'p', 'y', 'm', 'c', '0', '1' };

	//init ppm vars
	//The "us" prefix means the value of the variable is in microseconds
	int pin = 24;
	int pinMask = 1 << pin;		// Pin mask for accessing pin 24 through pigpio
	int usDelay = 300;			// Low pulse between high pulses
	int usFrameSize = 22500;	// Total ppm frame length
	int usTotalLength = 0;		// A counter to keep track of how long the wave is. 
								// For calculating the sync pulse between frames.
	int pulseCounter = 1;		// A counter to keep track of which pulse we are on (0-17)
	int wave;					// The pigpio wave id

	int numPulses = 18;
	gpioPulse_t frame[numPulses]; //The actual frame, composed of 18 pulses.

	int pi; //The pigpiod address thing

	//Connect to pigpio daemon and store the connection
	pi = pigpio_start(NULL, NULL);

	//We will be outputting ppm on pin 24
	set_mode(pi, pin, PI_OUTPUT);


	//Add channel delays and values
	for (char key: channelKeys)
	{

		//Add low delay
		//Update total length of channels for calculating sync pulse
		usTotalLength += usDelay;
		frame[pulseCounter].gpioOn = 0;
		frame[pulseCounter].gpioOff = pinMask;
		frame[pulseCounter].usDelay = usDelay;

		//move to next pulse
		++pulseCounter;

		//Add high channel value
		usTotalLength += channels.find(key)->second;
		frame[pulseCounter].gpioOn = pinMask;
		frame[pulseCounter].gpioOff = 0;
		frame[pulseCounter].usDelay = channels.find(key)->second - usDelay;

		++pulseCounter;
	}

	//Add last delay 
	//pulseCounter at 17
	usTotalLength += usDelay;
	frame[pulseCounter].gpioOn = 0;
	frame[pulseCounter].gpioOff = pinMask;
	frame[pulseCounter].usDelay = usDelay;

	//Move to beginning of frame in order to add sync
	pulseCounter = 0;
	
	//Add sync pulse
	frame[pulseCounter].gpioOn = pinMask;
	frame[pulseCounter].gpioOff = 0;
	frame[pulseCounter].usDelay = usFrameSize - usTotalLength - usDelay;

	//Send it out
	wave_clear(pi);
	wave_add_generic(pi, numPulses, frame);
	wave = wave_create(pi);
	wave_send_using_mode(pi, wave, PI_WAVE_MODE_REPEAT_SYNC);
	wave_delete(pi, wave);
}

void PinIO::getGPS()
{
}

void PinIO::getBarometer()
{
}

void PinIO::getCompass()
{
}

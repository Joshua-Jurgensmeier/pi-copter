#include "quadcopter.hpp"
#include <chrono>
#include <thread>
/*
Takes in the number of surfaces being updated and then a variable number of 
alternating chars (e.g. 't' for throttle) and values (-100--100)
*/
void Quadcopter::control(int numSurfacesUpdated, ...) //va_args are cool... I guess... I want python back...
{

	va_list listPointer;
	va_start(listPointer, numSurfacesUpdated);
	/*
		Adjust input value (-100--100) to output (1000--2000)
		-100 | 1000 | (low)
		   0 | 1500 | (neutral)
		 100 | 2000 | (high)
	*/
	 
	for( int i = 0 ; i < numSurfacesUpdated; i++ )
	{
		//get the next two args
		int key = va_arg(listPointer, int);
		int value = va_arg(listPointer, int);
		
		//update channelState with the newly passed values
		channelState[key] = (5 * value) + 1500; //mathmagic
	}

	//Update real life!
	pins.sendPPM(channelState);	//sendPPM doesn't change channelState
	
	va_end(listPointer);
}

void Quadcopter::arm()
{
	//To arm: Accessory0 high and throttle low ('0' = 2000 and 't' = 1000)
	channelState['0'] = 2000;
	channelState['t'] = 1000;

	//Update real life
	pins.sendPPM(channelState);

	//Time to run and hide.
	std::this_thread::sleep_for(std::chrono::seconds(3));
}

void Quadcopter::disarm()
{
	//To disarm: Accessory0 low and throttle low ('0' = 1000 and 't' = 1000)
	channelState['0'] = 1000;
	channelState['t'] = 1000;

	//Update real life
	pins.sendPPM(channelState);
}

void Quadcopter::backflip()
{
}

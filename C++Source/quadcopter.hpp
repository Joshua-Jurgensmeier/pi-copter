#pragma once
#include "pinIO.hpp"
#include <map>
#include <stdarg.h>
#include <utility>

class Quadcopter
{
public:
	Quadcopter();
	void control(int numargs, ...);
	void arm();
	void disarm();
	void backflip();

private:
	PinIO pins;

	/*

	channels
	1 | Throttle   |  t
	2 | Roll       |  r
	3 | Pitch	   |  p
	4 | Yaw		   |  y
	5 | FlightMode |  m <- 1000 for now, backflips for later
	6 | Collective |  c	<- probably not used...
	7 | Accessory0 |  0	<- for like arming
	8 | Accessory1 |  1	<- more backflips?

	
	Channel -> ppm value (1000-2000) 
	When Quadcopter::control() is called, only the surfaces being updated
	need to be passed in.  The last value that the unchanged surfaces had 
	is pulled out of channelState and given to pinIO::sendPPM()  */
	std::map<char, int> channelState = 
	{ 
		{'t', 1500}, 
		{'r', 1500},
		{'p', 1500}, 
		{'y', 1500}, 
		{'m', 1000}, 
		{'c', 1500}, 
		{'0', 1500}, 
		{'1', 1500} 
	};
};

Quadcopter::Quadcopter()
{
	
}
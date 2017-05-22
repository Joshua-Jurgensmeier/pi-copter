#pragma once
#include <pigpiod_if2.h>
#include <map>

class PinIO
{
public:
	PinIO();
	~PinIO();

	void sendPPM(std::map<char, int> &channelMap);
	void getGPS();
	void getBarometer();
	void getCompass();

private:
	
};

PinIO::PinIO()
{
}

PinIO::~PinIO()
{
}
#include <chrono>
#include <thread>
#include <iostream>
#include "quadcopter.hpp"
#include <ncurses.h>


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

int main()
{
	int throttle = 0;

	initscr();

	cbreak();
	noecho();
	nodelay(stdscr, TRUE);

	scrollok(stdscr, TRUE);

	//init sky-plexus quad
	Quadcopter spq1;

	std::cout << "Arming...";
	spq1.arm();

	std::cout << "Throttle up";
	// the number of surfaces being updated, the channel, the value
	while (getch() != ' ')
	{
		if (getch() == KEY_UP)
		{
			std::cout << "up";
		}
		else if (getch() == KEY_DOWN)
		{
			std::cout << "down";
		}
	}
	//spq1.control(1, 't', 80);

	//std::this_thread::sleep_for(std::chrono::seconds(3)); //I want python back...

	std::cout << "Disarming...";
	spq1.disarm();
}
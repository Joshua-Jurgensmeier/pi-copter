#include <chrono>
#include <thread>
#include <iostream>
#include "quadcopter.hpp"


/*

channels
1 | Throttle   |  t
2 | Roll       |  r
3 | Pitch          |  p
4 | Yaw            |  y
5 | FlightMode |  m <- for backflips?
6 | Collective |  c     <- probably not used...
7 | Accessory0 |  0     <- for like arming
8 | Accessory1 |  1     <- more backflips?

*/

int main()
{
        int throttle = 100;

        //init sky-plexus quad
        Quadcopter spq1;

        //std::cout << "Arming...";
        std::cout << "Arming..." << std::endl;
        spq1.arm();

        std::cout << "Throttle up" << std::endl;
	spq1.control(1, 't', throttle);

	std::this_thread::sleep_for(std::chrono::seconds(3)); //I want python back...

        std::cout << "Disarming..." << std::endl;
        spq1.disarm();

}

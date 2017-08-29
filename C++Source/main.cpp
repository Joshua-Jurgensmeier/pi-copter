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

	/*
        // Sorry for long line.
        std::cout << "Press [w] and then [ENTER] to increase throttle, [s] and then [ENTER] to decrease throttle, and [space] and [Enter] to terminate" << std::endl;

        char gottenChar;
        do
        {
                gottenChar = getchar();

                if (gottenChar == 's')
                {
                        std::cout << "down" << std::endl;
                        throttle -= 10;
                        gottenChar = '0';
                }
                else if (gottenChar == 'w')
                {
                        std::cout << "up" << std::endl;
                        throttle += 10;
                        gottenChar = '0';
                }

                // The number of surfaces being updated, the channel, the value.
                spq1.control(1, 't', throttle);

                std::cout << throttle << std::endl;

                //std::this_thread::sleep_for(std::chrono::seconds(1)); //I want python back...

        } while (gottenChar != ' ');*/

        std::cout << "Disarming..." << std::endl;
        spq1.disarm();

}

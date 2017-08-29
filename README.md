# sky-plexus

Python and C++ code for my autonomous quadcopter.  Code runs on a Raspberry Pi hooked up to a CC3D flight controller board.  Requires the pigpio python library.

To build, run this from sky-plexus directory:
g++ -Wall -std=c++11 -o main.out C++Source/pinIO.cpp C++Source/quadcopter.cpp C++Source/main.cpp -pthread -lrt -lpigpiod_if2

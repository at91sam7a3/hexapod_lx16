#include "lib/hexapod_kinematics/src/platform.hpp"
#include "lib/lx16lib/lx16driver.h"
#include <wiringPi.h>

static lx16driver driver("/dev/ttyS0", true);

void setServo(int id, double angle)
{
    int angleToLx = (angle +45.0 ) / 0.27;
    driver.ServoMoveTimeWrite(id,angleToLx,100);
}

void sleepMs(int sleepTime)
{
    ;
}

void turnOnPowerToLegs()
{
    wiringPiSetup ();
    pinMode (7,OUTPUT); //Turn on power relay
    digitalWrite (7,true);
}

int main(int argc, char *argv[])
{
    std::cout << (driver.isOperational() ? "Servo driver OK" : "Servo driver failed to start") << std::endl;
    turnOnPowerToLegs();
    hexapod::Platform platform(&sleepMs, &setServo);
    platform.ParkLegs();
    return 0;
}
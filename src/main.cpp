#include "../../hexapod_kinematics/src/platform.hpp"
#include "../../lx16lib/lx16driver.h"
#include <chrono>
#include <thread>
#include <wiringPi.h>

static lx16driver driver("/dev/ttyS0", true);

void setServo(int id, double angle)
{
    int angleToLx = (angle + 45.0) / 0.27;
    driver.ServoMoveTimeWrite(id, angleToLx, 100);
}

void sleepMs(int sleepTime)
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
}

void turnOnPowerToLegs()
{
    wiringPiSetup();
    pinMode(7, OUTPUT); // Turn on power relay
    digitalWrite(7, true);
}


void checkServos()
{
    std::cout<<"Checking connected servos"<<std::endl;
    for (int i =0 ; i<18; ++i)
    {
        std::cout<<"Servo #"<<i<<"...";
        int voltage=driver.ServoVoltageRead(i);
        if(voltage == 0)
        {
            std::cout<<"Error"<<std::endl;
            continue;
        }
        else
        {
            std::cout<<"OK"<<std::endl;
        }
        float volt = voltage / 1000;
        std::cout<<"Voltage = "<<volt<<std::endl;
        std::cout<<"Adjustments angle = " << driver.ServoAdjustAngleGet(i)<<std::endl;
        std::pair<int,int> bounds = driver.GetAngleLimits(i);
        std::cout<<"Limits "<<bounds.first<<" .. "<<bounds.second<<std::endl;
        std::cout<<"Current angle "<<driver.ServoPositionRead(i)<<std::endl;
        std::cout<<"Status = "<<(int)driver.GetServoErrorStatus<<std::endl;
    }
}

int main(int argc, char *argv[])
{
    std::cout << (driver.isOperational() ? "Servo driver OK"
                                         : "Servo driver failed to start")
              << std::endl;
    turnOnPowerToLegs();
    hexapod::Platform platform(&sleepMs, &setServo);
    checkServos();
    platform.parkLegs();
    std::cout << "To start moving, enter next data" << std::endl;
    float x, y, r = 0;

    std::cout << "X: ";
    std::cin >> x;
    std::cout << std::endl;
    std::cout << "Y: ";
    std::cin >> y;
    std::cout << std::endl;
    std::cout << "R: ";
    std::cin >> r;
    std::cout << std::endl;
   // platform.setVelocity({x, y}, r);
    //platform.startMovementThread();
    std::cout << "Movement started, press enter to exit" << std::endl;
    std::cin >> x;
    return 0;
}
#include "../lib/hexapod_kinematics/src/platform.hpp"
#include "../lib/lx16lib/lx16driver.h"
#include <chrono>
#include <thread>
#include <wiringPi.h>

static lx16driver driver("/dev/ttyS0", true);

void setServo(int id, double angle)
{
    std::cout << "------------" << std::endl;
    std::cout << "set motor "<<id<<" to angle "<<angle<<std::endl;
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

int main(int argc, char *argv[])
{
    std::cout << (driver.isOperational() ? "Servo driver OK"
                                         : "Servo driver failed to start")
              << std::endl;
    turnOnPowerToLegs();
    hexapod::Platform platform(&sleepMs, &setServo);
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
    platform.setVelocity({x, y}, r);
    platform.startMovementThread();
    std::cout << "Movement started, press enter to exit" << std::endl;
    std::cin >> x;
    return 0;
}
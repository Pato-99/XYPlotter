
#include <cmath>
#include "pico/stdlib.h"
#include "plotter.h"
#include "line.h"


Plotter::Plotter(MG90S pen, TMC2209 motorX, TMC2209 motorY)
    : pen(pen), motorX(motorX), motorY(motorY)
{}

void Plotter::penUp()
{
    this->pen.setLevel(this->penPwmLevelUp);
    this->penIsUp = true;
}

void Plotter::penDown()
{
    this->pen.setLevel(this->penPwmLevelDown);
    this->penIsUp = false;
}

void Plotter::transformCoordinates(double& x, double& y)
{
    double tmpX = (- x + y) / sqrt(2);
    double tmpY = (- x - y) / sqrt(2);

    x = tmpX;
    y = tmpY;
}

int Plotter::mmToSteps(double mm)
{
    double stepDistance = 0.002454;  // mm
    return mm * sqrt(2.0) / stepDistance;  // multiplied by sqrt(2) to compensate for the coreXY kinematics
}

void Plotter::move(double x, double y)
{
    Plotter::transformCoordinates(x, y);

    Point moveEnd = {mmToSteps(x), mmToSteps(y)};
    
    Line line(current, moveEnd);
    bool xDir = moveEnd.x >= current.x;
    bool yDir = moveEnd.y >= current.y;
    motorX.setDir(xDir);
    motorY.setDir(yDir);

    for ( const auto& point : line ) {
        if (point.x != current.x) {
            motorX.step();
        }
        if (point.y != current.y) {
            motorY.step();
        }
        current = point;
        sleep_us(delay);
    }
}

void Plotter::resetPosition() {
    this->current = {0, 0};
}



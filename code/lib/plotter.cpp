
#include <cmath>
#include <iostream>
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

void Plotter::rotateXY(double& x, double& y)
{
    double tmpX = (x - y) / sqrt(2);
    double tmpY = (x + y) / sqrt(2);

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
    Plotter::rotateXY(x, y);

    Point moveEnd = {mmToSteps(x), mmToSteps(y)};

    // std::cout << "\nCurrentX: " << this->currentX
    //           << "\nCurrentY " << this->currentY
    //           << "\nxSteps: " << xSteps
    //           << "\nySteps: " << ySteps << std::endl;
    
    Line line(current, moveEnd);
    for ( const auto& point : line ) {
        this->motorX.turnSteps(point.x - this->current.x, 0);
        this->motorY.turnSteps(point.y - this->current.y, 0);
        current = point;
        sleep_ms(delay);
    }

    std::cout << "OK\n";
}




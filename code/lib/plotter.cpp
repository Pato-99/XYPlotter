
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
    return mm * sqrt(2.0) / stepDistance;
}

void Plotter::move(double x, double y)
{
    Plotter::rotateXY(x, y);

    int xSteps = mmToSteps(x);
    int ySteps = mmToSteps(y);


    int diffX = xSteps - this->currentX;
    int diffY = ySteps - this->currentY;

    // std::cout << "\nCurrentX: " << this->currentX
    //           << "\nCurrentY " << this->currentY
    //           << "\nxSteps: " << xSteps
    //           << "\nySteps: " << ySteps << std::endl;
    
    int speed = 40;

    Line line({this->currentX, this->currentY}, {xSteps, ySteps});
    for ( const auto& point : line ) {
        this->motorX.turnSteps(point.x - this->currentX, speed);
        this->motorY.turnSteps(point.y - this->currentY, speed);
        this->currentX = point.x;
        this->currentY = point.y;
    }

    std::cout << "OK\n";

}




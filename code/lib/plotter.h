#ifndef PLOTTER_H
#define PLOTTER_H


#include "mg90s.h"
#include "tmc2209.h"
#include "line.h"


class Plotter
{
private:
    const MG90S pen;
    const TMC2209 motorX;
    const TMC2209 motorY;

    const uint16_t penPwmLevelUp = 5888;
    const uint16_t penPwmLevelDown = 4225;

    // state variables
    Point current = {0, 0};  // steps
    bool penIsUp = false;

    int delay = 40;

public:
    Plotter(MG90S pen, TMC2209 motorX, TMC2209 motorY);
    void penUp();
    void penDown();
    void move(double x, double y);
//    void homing();
private:
    static void rotateXY(double& x, double& y);
    static int mmToSteps(double mm);
};

#endif  // PLOTTER_H

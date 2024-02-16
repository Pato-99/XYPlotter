#ifndef PLOTTER_H
#define PLOTTER_H


#include "mg90s.h"
#include "tmc2209.h"

enum class Direction {LEFT, RIGHT, UP, DOWN, NOTHING};

class Plotter
{
private:
    const MG90S pen;
    const TMC2209 motorX;
    const TMC2209 motorY;

    const uint16_t penPwmLevelUp = 5888;
    const uint16_t penPwmLevelDown = 4225;

    // state variables
    int currentX = 0;  // steps
    int currentY = 0;  // steps
    bool penIsUp = false;

public:
    Plotter(MG90S pen, TMC2209 motorX, TMC2209 motorY);
    void penUp();
    void penDown();
    void move(double x, double y);
    void homing();
private:
    static void rotateXY(double& x, double& y);
    static int mmToSteps(double mm);

    Direction bUpDown(int x0, int y0, int x1, int y1);
    Direction bLeftRight(int x0, int y0, int x1, int y1);
    void b(int x0, int y0, int x1, int y1);

};

#endif  // PLOTTER_H

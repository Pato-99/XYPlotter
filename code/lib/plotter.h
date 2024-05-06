#ifndef PLOTTER_H
#define PLOTTER_H

#include <iostream>
#include "mg90s.h"
#include "tmc2209.h"
#include "line.h"
//#include "gcode.h"


// forward delcarations
class G0;
class G1;
class G2;
class G3;
class G4;
class G92;
class M3;
class M4;
class M98;
class M99;


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

    int delay = 100;

public:
    Plotter(MG90S pen, TMC2209 motorX, TMC2209 motorY);
    void penUp();
    void penDown();
    void move(double x, double y);
    void resetPosition();
    void setDelay(int d)
    {
        this->delay = d;
    }

    // gcodes
    void execute(const G0 *g0);
    void execute(const G1 *g1);
    void execute(const G2 *g2);
    void execute(const G3 *g3);
    void execute(const G4 *g4);
    void execute(const G92 *g92);
    void execute(const M3 *m3);
    void execute(const M4 *m4);
    void execute(const M98 *m98);
    void execute(const M99 *m99);

private:
//    void homing();
    static void transformCoordinates(double& x, double& y);
    static int mmToSteps(double mm);
};

#endif  // PLOTTER_H

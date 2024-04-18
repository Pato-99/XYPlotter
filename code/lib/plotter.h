#ifndef PLOTTER_H
#define PLOTTER_H


#include "mg90s.h"
#include "tmc2209.h"
#include "line.h"
#include "machine.h"


class Plotter : public Machine
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
    const MG90S& getPen();

    // gcodes
    void execute(const G0 *g0) override;
    void execute(const G1 *g1) override;
    void execute(const G2 *g2) override;
    void execute(const G3 *g3) override;
    void execute(const M3 *m3) override;
    void execute(const M4 *m4) override;
    void execute(const M99 *m99) override;
private:
//    void homing();
    static void transformCoordinates(double& x, double& y);
    static int mmToSteps(double mm);
};

#endif  // PLOTTER_H

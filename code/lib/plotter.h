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
    void executeG0(const G0 *g0) override;
    void executeG1(const G1 *g1) override;
    void executeG2(const G2 *g2) override;
    void executeG3(const G3 *g3) override;
    void executeM3(const M3 *m3) override;
    void executeM4(const M4 *m4) override;
    void executeM99(const M99 *m99) override;
private:
//    void homing();
    static void transformCoordinates(double& x, double& y);
    static int mmToSteps(double mm);
};

#endif  // PLOTTER_H

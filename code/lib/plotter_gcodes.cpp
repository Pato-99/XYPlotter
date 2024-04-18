
#include "plotter.h"
#include "gcode.h"

void Plotter::execute(const G0 *g0)
{
    this->move(g0->x, g0->y);
}

void Plotter::execute(const G1 *g1)
{
    this->move(g1->x, g1->y);
}

void Plotter::execute(const G2 *g2)
{
    // TODO; not implemented
}

void Plotter::execute(const G3 *g3)
{
    // TODO; not implemented
}

void Plotter::execute(const M3 *m3)
{
    this->penUp();
}

void Plotter::execute(const M4 *m4)
{
    this->penDown();
}

void Plotter::execute(const M99 *m99)
{
    this->pen.setLevel(m99->pwmLevel);
}

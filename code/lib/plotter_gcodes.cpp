
#include "plotter.h"
#include "gcode.h"

void Plotter::execute(const G0 *g0)
{
    this->move(g0->x, g0->y);
}

// G1 same as G0
void Plotter::execute(const G1 *g1)
{
    this->execute(static_cast<const G0*>(g1));
}

void Plotter::execute(const G2 *g2)
{
    // TODO; not implemented
}

void Plotter::execute(const G3 *g3)
{
    // TODO; not implemented
}

void Plotter::execute(const G4 *g4) {
    sleep_ms(g4->delay_ms);
}

void Plotter::execute(const G92 *g92)
{
    this->resetPosition();
}

void Plotter::execute(const M3 *m3)
{
    this->penUp();
}

void Plotter::execute(const M4 *m4)
{
    this->penDown();
}

void Plotter::execute(const M98 *m98)
{
    this->setDelay(m98->delay);
}

void Plotter::execute(const M99 *m99)
{
    this->pen.setLevel(m99->pwmLevel);
}

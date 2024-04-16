
#include "plotter.h"
#include "gcode.h"

void Plotter::executeG0(const G0 *g0)
{
    this->move(g0->x, g0->y);
}

void Plotter::executeG1(const G1 *g1)
{
    this->move(g1->x, g1->y);
}

void Plotter::executeG2(const G2 *g2) {

}

void Plotter::executeG3(const G3 *g3) {

}

void Plotter::executeM3(const M3 *m3) {

}

void Plotter::executeM4(const M4 *m4) {

}

void Plotter::executeM99(const M99 *m99) {

}

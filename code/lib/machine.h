#ifndef XYPLOTTER_MACHINE_H
#define XYPLOTTER_MACHINE_H

#include "gcode.h"

//
class G0;
class G1;
class G2;
class G3;
class M3;
class M4;
class M99;

class Machine
{
public:
    virtual void execute(const G0 *g0) = 0;
    virtual void execute(const G1 *g1) = 0;
    virtual void execute(const G2 *g2) = 0;
    virtual void execute(const G3 *g3) = 0;
    virtual void execute(const M3 *m3) = 0;
    virtual void execute(const M4 *m4) = 0;
    virtual void execute(const M99 *m99) = 0;
};


#endif //XYPLOTTER_MACHINE_H

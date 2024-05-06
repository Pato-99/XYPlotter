
#include <iostream>

#include "gcode.h"

void G0::dump(std::ostream &os) const {
    os << "gcode:\n{";
    os << "\n\ttype: " << "G";
    os << "\n\tnumber: " <<  0;
    os << "\n\tx: " << this->x;
    os << "\n\ty: " << this->y;
    os << "\n}\n";
}

void G2::dump(std::ostream &os) const {
    os << "gcode:\n{";
    os << "\n\ttype: " << "G";
    os << "\n\tnumber: " <<  2;
    os << "\n\tx: " << this->x;
    os << "\n\ty: " << this->y;
    os << "\n\ti: " << this->i;
    os << "\n\tj: " << this->j;
    os << "\n}\n";
}

void G4::dump(std::ostream &os) const {
    os << "gcode:\n{";
    os << "\n\ttype: " << "G";
    os << "\n\tnumber: " <<  4;
    os << "\n\tdelay_ms: " << this->delay_ms;
    os << "\n}\n";
}

void G92::dump(std::ostream &os) const {
    os << "gcode:\n{";
    os << "\n\ttype: " << "G";
    os << "\n\tnumber: " <<  92;
    os << "\n}\n";
}


void M3::dump(std::ostream &os) const {
    os << "gcode:\n{";
    os << "\n\ttype: " << "M";
    os << "\n\tnumber: " <<  3;
    os << "\n}\n";
}


void M4::dump(std::ostream &os) const {
    os << "gcode:\n{";
    os << "\n\ttype: " << "M";
    os << "\n\tnumber: " <<  4;
    os << "\n}\n";
}

void M98::dump(std::ostream &os) const {
    os << "gcode:\n{";
    os << "\n\ttype: " << "M";
    os << "\n\tnumber: " <<  98;
    os << "\n\tpwmLevel: " <<  this->delay;
    os << "\n}\n";
}


void M99::dump(std::ostream &os) const {
    os << "gcode:\n{";
    os << "\n\ttype: " << "M";
    os << "\n\tnumber: " <<  99;
    os << "\n\tpwmLevel: " <<  this->pwmLevel;
    os << "\n}\n";
}

std::ostream &operator<<(std::ostream &os, const AbstractGCode& gCode) {
    gCode.dump(os);
    return os;
}

template<class ConcreteGCode>
void GCode<ConcreteGCode>::execute(Plotter *machine) {
    machine->execute(static_cast<ConcreteGCode*>(this));
}


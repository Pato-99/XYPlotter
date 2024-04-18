
#include <iostream>

#include "gcode.h"


void G0::execute(Machine *machine) const {
    machine->execute(this);
}

void G0::dump(std::ostream &os) const {
    os << "gcode:\n{";
    os << "\n\ttype: " << "G";
    os << "\n\tnumber: " <<  0;
    os << "\n\tx: " << this->x;
    os << "\n\ty: " << this->y;
    os << "\n}\n";
}

void G2::execute(Machine *machine) const {
    machine->execute(this);
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

void M3::execute(Machine *machine) const {
    machine->execute(this);
}

void M3::dump(std::ostream &os) const {
    os << "gcode:\n{";
    os << "\n\ttype: " << "M";
    os << "\n\tnumber: " <<  3;
    os << "\n}\n";
}

void M4::execute(Machine *machine) const {
    machine->execute(this);
}

void M4::dump(std::ostream &os) const {
    os << "gcode:\n{";
    os << "\n\ttype: " << "M";
    os << "\n\tnumber: " <<  4;
    os << "\n}\n";
}

void M99::execute(Machine *machine) const {
    machine->execute(this);
}

void M99::dump(std::ostream &os) const {
    os << "gcode:\n{";
    os << "\n\ttype: " << "M";
    os << "\n\tnumber: " <<  99;
    os << "\n\tpwmLevel: " <<  this->pwmLevel;
    os << "\n}\n";
}

std::ostream &operator<<(std::ostream &os, const GCode& gCode) {
    gCode.dump(os);
    return os;
}

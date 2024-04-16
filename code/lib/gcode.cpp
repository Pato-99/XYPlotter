
#include <iostream>
#include <string>

#include "gcode.h"

std::ostream& G0::operator<<(std::ostream &os)
{
    os << "gcode:\n{";
    os << "\n\ttype: " << "G";
    os << "\n\tnumber: " <<  0;
    os << "\n\tx: " << this->x;
    os << "\n\ty: " << this->y;
    os << "\n}\n";
    return os;
}

void G0::execute(Machine *machine) const {
    machine->executeG0(this);
}

std::ostream& G2::operator<<(std::ostream &os)
{
    os << "gcode:\n{";
    os << "\n\ttype: " << "G";
    os << "\n\tnumber: " <<  2;
    os << "\n\tx: " << this->x;
    os << "\n\ty: " << this->y;
    os << "\n\ti: " << this->i;
    os << "\n\tj: " << this->j;
    os << "\n}\n";
    return os;
}

void G2::execute(Machine *machine) const {
    machine->executeG2(this);
}


std::ostream& M3::operator<<(std::ostream &os)
{
    os << "gcode:\n{";
    os << "\n\ttype: " << "M";
    os << "\n\tnumber: " <<  3;
    os << "\n}\n";
    return os;
}

void M3::execute(Machine *machine) const {
    machine->executeM3(this);
}


std::ostream& M4::operator<<(std::ostream &os)
{
    os << "gcode:\n{";
    os << "\n\ttype: " << "M";
    os << "\n\tnumber: " <<  4;
    os << "\n}\n";
    return os;
}

void M4::execute(Machine *machine) const {
    machine->executeM4(this);
}


std::ostream& M99::operator<<(std::ostream &os)
{
    os << "gcode:\n{";
    os << "\n\ttype: " << "M";
    os << "\n\tnumber: " <<  99;
    os << "\n\tpwmLevel: " <<  this->pwmLevel;
    os << "\n}\n";
    return os;
}

void M99::execute(Machine *machine) const {
    machine->executeM99(this);
}


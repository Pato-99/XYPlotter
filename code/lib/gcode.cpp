
#include <iostream>
#include <string>

#include "gcode.h"

void GCode::rotateXY()
{
    return;  // TODO
}

void GCode::dump()
{
    std::cout << "gcode:\n{";
    std::cout << "\n\ttype: " << (int)this->type;
    std::cout << "\n\tnumber: " <<  this->number;
    std::cout << "\n\tx: " << this->x;
    std::cout << "\n\ty: " << this->y;
    std::cout << "\n\ti: " << this->i;
    std::cout << "\n\tj: " << this->j;
    std::cout << "\n}\n";
}

GCodeLineParser::GCodeLineParser(std::string& gcodeLine)
    : gcodeLineStream(std::istringstream(gcodeLine)),
      gcode(GCode())
{
}

GCode GCodeLineParser::getGCode()
{
    return this->gcode;
}

bool GCodeLineParser::parse()
{
    this->gcodeLineStream >> this->gcode.type;
    if (this->gcodeLineStream.fail())
        return false;

    switch (this->gcode.type) {
        case 'G':
            return this->state_G();
        case 'M':
            return this->state_M();
        default:
            return false;
    }
}

bool GCodeLineParser::state_G()
{
    this->gcodeLineStream >> this->gcode.number;
    if (this->gcodeLineStream.fail())
        return false;

    switch (this->gcode.number) {
        case 0:
        case 1:
            return this->state_G0_G1();
        case 2:
        case 3:
            return this->state_G2_G3();
        case 28:
            return this->state_G28();
        default:
            return false;
    }
}

bool GCodeLineParser::state_G0_G1()
{
    char c;
    double value;

    while (true) {
        this->gcodeLineStream >> c >> value;
        if (this->gcodeLineStream.fail())
            break;

        switch (c) {
            case 'X':
                this->gcode.x = value;
                break;
            case 'Y':
                this->gcode.y = value;
                break;
            default:
                return false;
        }
    }

    if (this->gcode.x == 0 && this->gcode.y == 0)
        return false;
    
    // this->gcode.rotateXY();
    return true;
}


bool GCodeLineParser::state_G2_G3()
{
    char x, y, i, j;
    return this->gcodeLineStream >> x >> this->gcode.x
                                 >> y >> this->gcode.y
                                 >> i >> this->gcode.i
                                 >> j >> this->gcode.j &&
            x == 'X' &&
            y == 'Y' &&
            i == 'I' &&
            j == 'J';
}

bool GCodeLineParser::state_G28()
{
    return true;  // TODO
}


bool GCodeLineParser::state_M()
{
    this->gcodeLineStream >> this->gcode.number;
    if (this->gcodeLineStream.fail())
        return false;
    switch (this->gcode.number) {
        case 3:
            return true;
        case 4:
            return true;
        case 99:
            return this->state_M99();
        default:
            return false;
    }
}

bool GCodeLineParser::state_M99()
{
    this->gcodeLineStream >> this->gcode.x;
    return !this->gcodeLineStream.fail();
}

bool GCodeParser::getGCode(GCode& gcode)
{
    if (! std::getline(std::cin, this->line))
        return false;
    
    GCodeLineParser parser(this->line);
    
    if (! parser.parse())
        return false;
    
    gcode = parser.getGCode();
    return true;
}
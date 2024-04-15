
#include <iostream>
#include <string>

#include "gcode.h"

void G0::execute(Plotter plotter)
{
    plotter.move(this->x, this->y);
}

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

void G2::execute(Plotter plotter)
{
    // TODO
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

void M3::execute(Plotter plotter)
{
    plotter.penUp();
}

std::ostream& M3::operator<<(std::ostream &os)
{
    os << "gcode:\n{";
    os << "\n\ttype: " << "M";
    os << "\n\tnumber: " <<  3;
    os << "\n}\n";
    return os;
}

void M4::execute(Plotter plotter)
{
    plotter.penDown();
}

std::ostream& M4::operator<<(std::ostream &os)
{
    os << "gcode:\n{";
    os << "\n\ttype: " << "M";
    os << "\n\tnumber: " <<  4;
    os << "\n}\n";
    return os;
}

void M99::execute(Plotter plotter)
{
    plotter.getPen().setLevel(this->pwmLevel);
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


GCodeLineParser::GCodeLineParser(std::string& gcodeLine)
    : gcodeLineStream(std::istringstream(gcodeLine))
{
}

std::unique_ptr<GCode> GCodeLineParser::parse()
{
    char type;
    this->gcodeLineStream >> type;
    if (this->gcodeLineStream.fail())
        return nullptr;

    switch (type) {
        case 'G':
            return this->state_G();
        case 'M':
            return this->state_M();
        default:
            return nullptr;
    }
}

std::unique_ptr<GCode> GCodeLineParser::state_G()
{
    int number;
    this->gcodeLineStream >> number;
    if (this->gcodeLineStream.fail())
        return nullptr;

    switch (number) {
        case 0:
        case 1:
            return this->state_G0_G1();
        case 2:
        case 3:
            return this->state_G2_G3();
        case 28:
            return this->state_G28();
        default:
            return nullptr;
    }
}

std::unique_ptr<GCode> GCodeLineParser::state_G0_G1()
{
    char c;
    double value, x, y;

    while (true) {
        this->gcodeLineStream >> c >> value;
        if (this->gcodeLineStream.fail())
            break;
        switch (c) {
            case 'X':
                x = value;
                break;
            case 'Y':
                y = value;
                break;
            default:
                return nullptr;
        }
    }
    return std::make_unique<G0>(x, y);
}


std::unique_ptr<GCode> GCodeLineParser::state_G2_G3()
{
    char x, y, i, j;
    double xx, yy, ii, jj;
    this->gcodeLineStream >> x >> xx >> y >> yy >> i >> ii >> j >> jj;

    if (this->gcodeLineStream.fail() || x != 'X' || y != 'Y' || i != 'I' || j != 'J' )
        return nullptr;

    return std::make_unique<G2>(xx, yy, ii, jj);
}

std::unique_ptr<GCode> GCodeLineParser::state_G28()
{
    return nullptr;  // TODO
}


std::unique_ptr<GCode> GCodeLineParser::state_M()
{
    int number;
    this->gcodeLineStream >> number;
    if (this->gcodeLineStream.fail())
        return nullptr;
    switch (number) {
        case 3:
            return std::make_unique<M3>();
        case 4:
            return std::make_unique<M4>();
        case 99:
            return this->state_M99();
        default:
            return nullptr;
    }
}

std::unique_ptr<GCode> GCodeLineParser::state_M99()
{
    double pwmLevel;
    this->gcodeLineStream >> pwmLevel;
    if (this->gcodeLineStream.fail())
        return nullptr;
    return std::make_unique<M99>(pwmLevel);
}

std::unique_ptr<GCode> GCodeParser::getGCode() {
    if (!std::getline(std::cin, this->line))
        return nullptr;

    GCodeLineParser parser(this->line);

    return parser.parse();
}

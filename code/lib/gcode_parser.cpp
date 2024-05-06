#include <iostream>

#include "gcode_parser.h"

GCodeLineParser::GCodeLineParser(std::string& gcodeLine)
        : gcodeLineStream(std::istringstream(gcodeLine))
{
}

std::unique_ptr<AbstractGCode> GCodeLineParser::parse()
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

std::unique_ptr<AbstractGCode> GCodeLineParser::state_G()
{
    int number;
    this->gcodeLineStream >> number;
    if (this->gcodeLineStream.fail())
        return nullptr;

    switch (number) {
        case 0:
        case 1:
            return this->state_G0_G1(number);
        case 2:
        case 3:
            return this->state_G2_G3();
        case 4:
            return this->state_G4();
        case 28:
            return this->state_G28();
        case 92:
            return std::make_unique<G92>();
        default:
            return nullptr;
    }
}

std::unique_ptr<AbstractGCode> GCodeLineParser::state_G0_G1(int number)
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
            case 'F':
                break;
            default:
                return nullptr;
        }
    }

    if (number == 0)
        return std::make_unique<G0>(x, y);
    return std::make_unique<G1>(x, y);
}


std::unique_ptr<AbstractGCode> GCodeLineParser::state_G2_G3()
{
    char x, y, i, j;
    double xx, yy, ii, jj;
    this->gcodeLineStream >> x >> xx >> y >> yy >> i >> ii >> j >> jj;

    if (this->gcodeLineStream.fail() || x != 'X' || y != 'Y' || i != 'I' || j != 'J' )
        return nullptr;

    return std::make_unique<G2>(xx, yy, ii, jj);
}


std::unique_ptr<AbstractGCode> GCodeLineParser::state_G4()
{
    char c;
    double value, delay_ms;

    this->gcodeLineStream >> c >> value;
    if (this->gcodeLineStream.fail())
        return nullptr;

    switch (c) {
        case 'P':
            delay_ms = value;
            break;
        case 'S':
            delay_ms = value * 1000;
            break;
        default:
            return nullptr;
    }
    return std::make_unique<G4>(delay_ms);
}

std::unique_ptr<AbstractGCode> GCodeLineParser::state_G28()
{
    return nullptr;  // TODO
}


std::unique_ptr<AbstractGCode> GCodeLineParser::state_M()
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
        case 98:
            return this->state_M98();
        case 99:
            return this->state_M99();
        default:
            return nullptr;
    }
}

std::unique_ptr<AbstractGCode> GCodeLineParser::state_M98()
{
    int delay;
    this->gcodeLineStream >> delay;
    if (this->gcodeLineStream.fail())
        return nullptr;
    return std::make_unique<M98>(delay);
}

std::unique_ptr<AbstractGCode> GCodeLineParser::state_M99()
{
    double pwmLevel;
    this->gcodeLineStream >> pwmLevel;
    if (this->gcodeLineStream.fail())
        return nullptr;
    return std::make_unique<M99>(pwmLevel);
}

std::unique_ptr<AbstractGCode> GCodeParser::getGCode() {
    if (!std::getline(std::cin, this->line))
        return nullptr;

    GCodeLineParser parser(this->line);

    return parser.parse();
}

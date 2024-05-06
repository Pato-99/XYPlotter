#ifndef XYPLOTTER_GCODE_PARSER_H
#define XYPLOTTER_GCODE_PARSER_H

#include <sstream>
#include <ostream>
#include <string>
#include <memory>

#include "gcode.h"

class GCodeLineParser
{
private:
    std::istringstream gcodeLineStream;

public:
    explicit GCodeLineParser(std::string& gcodeLine);
    std::unique_ptr<AbstractGCode> parse();

private:
    std::unique_ptr<AbstractGCode> state_G();
    std::unique_ptr<AbstractGCode> state_G0_G1(int number);
    std::unique_ptr<AbstractGCode> state_G2_G3();
    std::unique_ptr<AbstractGCode> state_G4();
    std::unique_ptr<AbstractGCode> state_G28();
    std::unique_ptr<AbstractGCode> state_M();
    std::unique_ptr<AbstractGCode> state_M98();
    std::unique_ptr<AbstractGCode> state_M99();
};


class GCodeParser
{
private:
    std::string line;
    // GCode gcodeBuffer[10];
public:
    GCodeParser() = default;
    std::unique_ptr<AbstractGCode> getGCode();
};


#endif //XYPLOTTER_GCODE_PARSER_H

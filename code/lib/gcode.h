#ifndef GCODE_H
#define GCODE_H

#include <sstream>
#include <string>

// enum class GCodeStatus {OK, BAD};
enum class GCodeType {G, M, UNKNOWN};

struct GCode
{
    char type = 'U';
    int number = 0;  // TODO int8_t
    double x = 0;  // TODO float? enough percision?
    double y = 0;
    double i = 0;
    double j = 0;

    // apply 45 deg rotation because of coreXY kinematics
    void rotateXY();
    void dump();
};

class GCodeLineParser
{
private:
    std::istringstream gcodeLineStream;
    GCode gcode;

public:
    GCodeLineParser(std::string& gcodeLine);
    GCode getGCode();
    bool parse();
    bool state_G();
    bool state_G0_G1();
    bool state_G2_G3();
    bool state_G28();
    bool state_M();
    bool state_M99();
};


class GCodeParser
{
private:
    std::string line;
    // GCode gcodeBuffer[10];
public:
    GCodeParser() = default;
    bool getGCode(GCode& gcode);
};

#endif  // GCODE_H

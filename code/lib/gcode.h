#ifndef GCODE_H
#define GCODE_H

#include <sstream>
#include <ostream>
#include <string>
#include <memory>

#include "plotter.h"

// enum class GCodeStatus {OK, BAD};
enum class GCodeType {G, M, UNKNOWN};

class GCode
{
public:
    virtual void execute(Plotter plotter) = 0;
    virtual std::ostream& operator << (std::ostream& os) = 0;
};

class G0 : public GCode
{
private:
    double x;
    double y;
public:
    G0(double x, double y) : x(x), y(y) {};
    void execute(Plotter plotter) override;
    std::ostream& operator << (std::ostream& os) override;
};

class G1 : private G0
{};


class GCodeLineParser
{
private:
    std::istringstream gcodeLineStream;
    std::unique_ptr<GCode> gcode;

public:
    explicit GCodeLineParser(std::string& gcodeLine);

    std::unique_ptr<GCode> getGCode();
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

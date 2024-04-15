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

class G2 : public GCode
{
private:
    double x, y, i, j;
public:
    G2(double x, double y, double i, double j) : x(x), y(y), i(i), j(j) {};
    void execute(Plotter plotter) override;
    std::ostream& operator << (std::ostream& os) override;
};

class G3 : private G2
{};

class M3 : public GCode
{
public:
    void execute(Plotter plotter) override;
    std::ostream& operator << (std::ostream &os) override;
};

class M4 : public GCode
{
public:
    void execute(Plotter plotter) override;
    std::ostream& operator << (std::ostream &os) override;
};

class M99 : public GCode
{
private:
    uint16_t pwmLevel;
public:
    explicit M99(uint16_t pwmLevel) : pwmLevel(pwmLevel) {};
    void execute(Plotter plotter) override;
    std::ostream& operator << (std::ostream &os) override;
};


class GCodeLineParser
{
private:
    std::istringstream gcodeLineStream;

public:
    explicit GCodeLineParser(std::string& gcodeLine);
    std::unique_ptr<GCode> parse();

private:
    std::unique_ptr<GCode> state_G();
    std::unique_ptr<GCode> state_G0_G1();
    std::unique_ptr<GCode> state_G2_G3();
    std::unique_ptr<GCode> state_G28();
    std::unique_ptr<GCode> state_M();
    std::unique_ptr<GCode> state_M99();
};


class GCodeParser
{
private:
    std::string line;
    // GCode gcodeBuffer[10];
public:
    GCodeParser() = default;
    std::unique_ptr<GCode> getGCode();
};

#endif  // GCODE_H

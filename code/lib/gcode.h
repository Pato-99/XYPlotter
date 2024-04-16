#ifndef GCODE_H
#define GCODE_H

#include <ostream>
#include <memory>

#include "machine.h"

class Machine;

// enum class GCodeStatus {OK, BAD};
enum class GCodeType {G, M, UNKNOWN};

class GCode
{
public:
    virtual void execute(Machine *machine) const = 0;
    virtual std::ostream& operator << (std::ostream& os) = 0;
};

class G0 : public GCode
{
public:
    double x;
    double y;
    G0(double x, double y) : x(x), y(y) {};
    void execute(Machine *machine) const override;
    std::ostream& operator << (std::ostream& os) override;
};

class G1 : public G0
{};

class G2 : public GCode
{
public:
    double x, y, i, j;
    G2(double x, double y, double i, double j) : x(x), y(y), i(i), j(j) {};
    void execute(Machine *machine) const override;
    std::ostream& operator << (std::ostream& os) override;
};

class G3 : private G2
{};

class M3 : public GCode
{
public:
    void execute(Machine *machine) const override;
    std::ostream& operator << (std::ostream &os) override;
};

class M4 : public GCode
{
public:
    void execute(Machine *machine) const override;
    std::ostream& operator << (std::ostream &os) override;
};

class M99 : public GCode
{
public:
    uint16_t pwmLevel;
    explicit M99(uint16_t pwmLevel) : pwmLevel(pwmLevel) {};
    void execute(Machine *machine) const override;
    std::ostream& operator << (std::ostream &os) override;
};


#endif  // GCODE_H

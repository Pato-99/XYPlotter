#ifndef GCODE_H
#define GCODE_H

#include <ostream>
#include <memory>

#include "plotter.h"

class Plotter;

// enum class GCodeStatus {OK, BAD};
enum class GCodeType {G, M, UNKNOWN};

class AbstractGCode
{
public:
    virtual void dump(std::ostream &os) const = 0;
    virtual void execute(Plotter *machine) = 0;
    virtual ~AbstractGCode() = default;
    friend std::ostream& operator << (std::ostream & os, const AbstractGCode& gCode);
};


// CRTP Pattern
template<class ConcreteGCode>
class GCode : public AbstractGCode
{
public:
    void execute(Plotter *machine) override;
};


class G0 : public GCode<G0>
{
public:
    double x;
    double y;
    G0(double x, double y) : x(x), y(y) {};
    void dump(std::ostream &os) const override;
};

class G1 : public G0
{
public:
    G1(double x, double y) : G0(x, y) {};
};

class G2 : public GCode<G2>
{
public:
    double x, y, i, j;
    G2(double x, double y, double i, double j) : x(x), y(y), i(i), j(j) {};
    void dump(std::ostream &os) const override;
};

class G3 : public G2
{
public:
    G3(double x, double y, double i, double j) : G2(x, y, i, j) {};
};

class G4 : public GCode<G4>
{
public:
    double delay_ms;
    explicit G4(double delay_ms) : delay_ms(delay_ms) {};
    void dump(std::ostream &os) const override;
};

// Reset coordinates to zero
class G92 : public GCode<G92>
{
public:
    void dump(std::ostream &os) const override;
};


// Pen up
class M3 : public GCode<M3>
{
public:
    void dump(std::ostream &os) const override;
};

// Pen down
class M4 : public GCode<M4>
{
public:
    void dump(std::ostream &os) const override;
};

class M98 : public GCode<M98>
{
public:
    int delay;
    explicit M98(int delay) : delay(delay) {};
    void dump(std::ostream &os) const override;
};

class M99 : public GCode<M99>
{
public:
    uint16_t pwmLevel;
    explicit M99(uint16_t pwmLevel) : pwmLevel(pwmLevel) {};
    void dump(std::ostream &os) const override;
};


#endif  // GCODE_H

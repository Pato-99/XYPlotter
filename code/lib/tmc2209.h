#ifndef TMC2209_H
#define TMC2209_H


enum class MICROSTEPPING {MS8, MS16, MS32, MS64};


class TMC2209
{
private:
    const uint en;
    const uint stp;
    const uint dir;
    const uint ms1;
    const uint ms2;
    const uint diag;

public:
    TMC2209(uint en,
            uint stp,
            uint dir,
            uint ms1,
            uint ms2,
            uint diag);

    void enable();
    void disable();
    void setDir(bool dir);
    void step();
    void turnSteps(int n, int delay);
    void setMicrostepping(MICROSTEPPING ms);
};


#endif  // TMC2209

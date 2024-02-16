#ifndef HOLDER_H
#define HOLDER_H

#include "mg90s.h"

enum class ClampState {GRAB, RELEASE};
enum class LiftState {UP, DOWN};

class Holder
{
public:
    const MG90S clamp;
    const MG90S lift;
private:
    ClampState clamp_state;
    LiftState lift_state;


public:
    Holder(const MG90S clamp, const MG90S lift);

    void grab();
    void release();

    void penUp();
    void penDown();
};

#endif  // HOLDER_H
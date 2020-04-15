#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include "motor.h"

class MotorDriver
{
public:
    MotorDriver(int mRFP, int mRRP, int mLFP, int mLRP);

    void allStop();
    void up();
    void down();
    void right();
    void left();

private:

    enum class CarState {
        STOPPED,
        FORWARD,
        REVERSE,
        TURN_LEFT,
        TURN_RIGHT,
        PIVOT_LEFT,
        PIVOT_RIGHT,
        REV_TURN_LEFT,
        REV_TURN_RIGHT
    };

    Motor _motorR;
    Motor _motorL;

    CarState _state;
};

#endif // MOTORDRIVER_H

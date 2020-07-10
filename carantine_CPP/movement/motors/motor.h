#ifndef MOTOR_H
#define MOTOR_H

#include <vector>
#include <wiringPi.h>
#include <softPwm.h>

/*
 * This class handles the behaviour of a single motor.
 *
 * STEP_ZERO to _FIVE are the possible PWM duty-cycle steps the motor's pins can take.
 */

#define STEP_ZERO 0
#define STEP_ONE 20
#define STEP_TWO 40
#define STEP_THREE 60
#define STEP_FOUR 80
#define STEP_FIVE 100

enum class MotorState {
    FORWARD,
    REVERSE,
    STOPPED
};

class Motor
{
public:
    Motor(int forwardPINNumber, int reversePINNumber);

    void stepUp();
    void stepDown();
    void stop();
    MotorState getState();
    unsigned int getAbsSpeed();

private:
    const int _forwardPINNumber;
    const int _reversePINNumber;

    void initializePWM();

    void setFPValue(unsigned int index);
    void setRPValue(unsigned int index);

    unsigned int _FPIndex;
    unsigned int _RPIndex;

    MotorState _status;
    std::vector<int> _steps;
};

#endif // MOTOR_H

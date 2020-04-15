#ifndef MOTOR_H
#define MOTOR_H

#include <vector>

/*
 * This class handles the behaviour of a single motor.
 *
 */

enum class Direction {
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

private:
    const int _forwardPINNumber;
    const int _reversePINNumber;

    // We might not even need these, and just write the value to pins directly
    int _forwardPINValue;
    int _reversePINValue;

    void setFPValue(unsigned int index);
    void setRPValue(unsigned int index);

    unsigned int _FPIndex;
    unsigned int _RPIndex;

    Direction _direction;
    std::vector<int> _steps;
    int _maxStep;
};

#endif // MOTOR_H

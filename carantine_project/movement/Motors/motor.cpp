#include "motor.h"

Motor::Motor(int forwardPINNumber, int reversePINNumber) : _forwardPINNumber(forwardPINNumber),
                                                           _reversePINNumber(reversePINNumber)
{
    _direction = Direction::STOPPED;

    _steps = {0, 20, 40, 60, 80, 100};
    _maxStep = _steps[_steps.size()];

    _FPIndex = 0;
    _RPIndex = 0;

    setFPValue(_FPIndex);
    setRPValue(_RPIndex);
}

void Motor::setFPValue(unsigned int index)
{
    if (index < _steps.size()) {
        _forwardPINValue = _steps[index];
    }

    //todo : we could use these functions to write the pwm value immediately.
}

void Motor::setRPValue(unsigned int index)
{
    if (index < _steps.size()) {
        _reversePINValue = _steps[index];
    }
}

void Motor::stepUp()
{
    switch (_direction) {
        case Direction::STOPPED :
        {
            setFPValue(++_FPIndex);
            _direction = Direction::FORWARD;
            break;

        }
        case Direction::FORWARD :
        {
            if (_FPIndex == _steps.size() - 1) {
                break;
            } else {
                setFPValue(++_FPIndex);
            }
            break;
        }
        case Direction::REVERSE :
        {
            if (_RPIndex == 1) {
                setRPValue(--_RPIndex);
                _direction = Direction::STOPPED;
            } else {
                setRPValue(--_RPIndex);
            }
            break;
        }
    }

}

void Motor::stop()
{
    setFPValue(0);
    setRPValue(0);
    _direction = Direction::STOPPED;
}

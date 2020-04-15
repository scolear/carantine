#include "motor.h"

Motor::Motor(int forwardPINNumber, int reversePINNumber) : _forwardPINNumber(forwardPINNumber),
                                                           _reversePINNumber(reversePINNumber)
{
    initializePWM();

    _direction = Direction::STOPPED;

    _steps = {STEP_ZERO, STEP_ONE, STEP_TWO, STEP_THREE, STEP_FOUR, STEP_FIVE};
    _maxStep = _steps[_steps.size()];
}

void Motor::initializePWM()
{
    // possible streamlining: shut down the threads while motor is stopped

    softPwmCreate(_forwardPINNumber, 0, 100);
    softPwmCreate(_reversePINNumber, 0, 100);

    _FPIndex = 0;
    _RPIndex = 0;

    setFPValue(_FPIndex);
    setRPValue(_RPIndex);
}

void Motor::setFPValue(unsigned int index)
{
    if (index < _steps.size()) {
        softPwmWrite(_forwardPINNumber, _steps[index]);
    }
}

void Motor::setRPValue(unsigned int index)
{
    if (index < _steps.size()) {
        softPwmWrite(_reversePINNumber, _steps[index]);
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

void Motor::stepDown()
{
    switch (_direction) {
        case Direction::STOPPED :
        {
            setRPValue(++_RPIndex);
            _direction = Direction::REVERSE;
            break;

        }
        case Direction::FORWARD :
        {
            if (_FPIndex == 1) {
                setFPValue(--_FPIndex);
                _direction = Direction::STOPPED;
            } else {
                setFPValue(--_FPIndex);
            }
            break;
        }
        case Direction::REVERSE :
        {
            if (_RPIndex == _steps.size() - 1) {
                break;
            } else {
                setRPValue(++_RPIndex);
            }
            break;
        }
    }
}

void Motor::stop()
{
    _FPIndex = 0;
    _RPIndex = 0;
    setFPValue(_FPIndex);
    setRPValue(_RPIndex);
    _direction = Direction::STOPPED;
}

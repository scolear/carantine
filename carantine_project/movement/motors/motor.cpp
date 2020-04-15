#include "motor.h"

Motor::Motor(int forwardPINNumber, int reversePINNumber) : _forwardPINNumber(forwardPINNumber),
                                                           _reversePINNumber(reversePINNumber)
{
    initializePWM();

    _status = MotorState::STOPPED;

    _steps = {STEP_ZERO, STEP_ONE, STEP_TWO, STEP_THREE, STEP_FOUR, STEP_FIVE};
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
    switch (_status) {
        case MotorState::STOPPED :
        {
            setFPValue(++_FPIndex);
            _status = MotorState::FORWARD;
            break;

        }
        case MotorState::FORWARD :
        {
            if (_FPIndex == _steps.size() - 1) {
                break;
            } else {
                setFPValue(++_FPIndex);
            }
            break;
        }
        case MotorState::REVERSE :
        {
            setRPValue(--_RPIndex);

            if (_RPIndex == 0)
                _status = MotorState::STOPPED;
            break;
        }
    }

}

void Motor::stepDown()
{
    switch (_status) {
        case MotorState::STOPPED :
        {
            setRPValue(++_RPIndex);
            _status = MotorState::REVERSE;
            break;

        }
        case MotorState::FORWARD :
        {
            setFPValue(--_FPIndex);

            if (_FPIndex == 0)
                _status = MotorState::STOPPED;
            break;
        }
        case MotorState::REVERSE :
        {
            // todo: refactor these

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
    _status = MotorState::STOPPED;
}

MotorState Motor::getState()
{
    return _status;
}

unsigned int Motor::getAbsSpeed()
{
    switch (_status) {
        case MotorState::STOPPED :
        {
            return 0;
        }
        case MotorState::FORWARD :
        {
            return _FPIndex;
        }
        case MotorState::REVERSE :
        {
            return _RPIndex;
        }
    }
    return 0;
}

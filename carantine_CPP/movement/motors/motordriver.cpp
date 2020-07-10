#include "motordriver.h"

MotorDriver::MotorDriver(int mRFP, int mRRP, int mLFP, int mLRP) : _motorR(mRFP, mRRP),
                                                                   _motorL(mLFP, mLRP)
{
    _state = CarState::STOPPED;
}

void MotorDriver::allStop()
{
    _motorL.stop();
    _motorR.stop();
    _state = CarState::STOPPED;
}

void MotorDriver::up()
{
    switch (_state)
    {
        case CarState::STOPPED :

            _motorL.stepUp();
            _motorR.stepUp();
            _state = CarState::FORWARD;
            break;

        case CarState::FORWARD :

            _motorL.stepUp();
            _motorR.stepUp();
            break;

        case CarState::REVERSE :

            _motorL.stepUp();
            _motorR.stepUp();
            if (_motorL.getState() == MotorState::STOPPED && _motorR.getState() == MotorState::STOPPED) {
                _state = CarState::STOPPED;
            }
            break;

        case CarState::TURN_LEFT :

            _motorL.stepUp();
            if (_motorL.getAbsSpeed() == _motorR.getAbsSpeed()) {
                _state = CarState::FORWARD;
            }
            break;

        case CarState::TURN_RIGHT :

            _motorR.stepUp();
            if (_motorL.getAbsSpeed() == _motorR.getAbsSpeed()) {
                _state = CarState::FORWARD;
            }
            break;

        case CarState::PIVOT_LEFT :
        case CarState::PIVOT_RIGHT :
        case CarState::REV_TURN_LEFT :
        case CarState::REV_TURN_RIGHT :

            allStop();
            break;
    }
}

void MotorDriver::down()
{
    switch (_state)
    {
        case CarState::STOPPED :

            _motorL.stepDown();
            _motorR.stepDown();
            _state = CarState::REVERSE;
            break;

        case CarState::FORWARD :

            _motorL.stepDown();
            _motorR.stepDown();
            if (_motorL.getState() == MotorState::STOPPED && _motorR.getState() == MotorState::STOPPED) {
                _state = CarState::STOPPED;
            }
            break;

        case CarState::REVERSE :

            _motorL.stepDown();
            _motorR.stepDown();
            break;

        case CarState::TURN_LEFT :

            _motorR.stepDown();

            if (_motorR.getAbsSpeed() == 0) {
                _state = CarState::STOPPED;
            } else if ( _motorL.getAbsSpeed() == _motorR.getAbsSpeed()) {
                _state = CarState::FORWARD;
            }
            break;

        case CarState::TURN_RIGHT :

            _motorL.stepDown();

            if (_motorL.getAbsSpeed() == 0) {
                _state = CarState::STOPPED;
            } else if ( _motorL.getAbsSpeed() == _motorR.getAbsSpeed()) {
                _state = CarState::FORWARD;
            }
            break;

        case CarState::PIVOT_LEFT :
        case CarState::PIVOT_RIGHT :
        case CarState::REV_TURN_LEFT :
        case CarState::REV_TURN_RIGHT :

            allStop();
            break;
    }
}

void MotorDriver::right()
{
    switch (_state)
    {
        case CarState::STOPPED :

            _motorL.stepUp();
            _motorR.stepDown();
            _state = CarState::PIVOT_RIGHT;
            break;

        case CarState::FORWARD :

            _motorR.stepDown();
            _state = CarState::TURN_RIGHT;
            break;

        case CarState::REVERSE :

            _motorR.stepUp();
            _state = CarState::REV_TURN_RIGHT;
            break;

        case CarState::TURN_LEFT :

            _motorL.stepUp();
            if (_motorL.getAbsSpeed() == _motorR.getAbsSpeed()) {
                _state = CarState::FORWARD;
            }
            break;

        case CarState::TURN_RIGHT :

            _motorR.stepDown();
            if (_motorR.getState() == MotorState::REVERSE) {
                _state = CarState::PIVOT_RIGHT;
            }
            break;

        case CarState::PIVOT_LEFT :

            if (_motorL.getAbsSpeed() == _motorR.getAbsSpeed())
            {
                _motorL.stepUp();
                _motorR.stepDown();
                _state = CarState::STOPPED;
            }
            else
            {
                if (_motorL.getAbsSpeed() > 1) {
                    _motorL.stepUp();
                }
                if (_motorR.getAbsSpeed() > 1) {
                    _motorR.stepDown();
                }
            }

            break;

        case CarState::PIVOT_RIGHT :

            _motorR.stepDown();
            _motorL.stepUp();
            break;

        case CarState::REV_TURN_LEFT :

            _motorL.stepDown();
            if (_motorL.getAbsSpeed() == _motorR.getAbsSpeed()) {
                _state = CarState::REVERSE;
            }
            break;

        case CarState::REV_TURN_RIGHT :

            break;
    }
}

void MotorDriver::left()
{
    switch (_state)
    {
        case CarState::STOPPED :

            _motorR.stepUp();
            _motorL.stepDown();
            _state = CarState::PIVOT_LEFT;
            break;

        case CarState::FORWARD :

            _motorL.stepDown();
            _state = CarState::TURN_LEFT;
            break;

        case CarState::REVERSE :

            _motorL.stepUp();
            _state = CarState::REV_TURN_LEFT;
            break;

        case CarState::TURN_LEFT :

            _motorL.stepDown();
            if (_motorL.getState() == MotorState::REVERSE) {
                _state = CarState::PIVOT_LEFT;
            }
            break;

        case CarState::TURN_RIGHT :

            _motorR.stepUp();
            if (_motorL.getAbsSpeed() == _motorR.getAbsSpeed()) {
                _state = CarState::FORWARD;
            }
            break;

        case CarState::PIVOT_LEFT :

            _motorR.stepUp();
            _motorL.stepDown();
            break;

        case CarState::PIVOT_RIGHT :

            if (_motorL.getAbsSpeed() == _motorR.getAbsSpeed())
            {
                _motorR.stepUp();
                _motorL.stepDown();
                _state = CarState::STOPPED;
            }
            else
            {
                if (_motorL.getAbsSpeed() > 1) {
                    _motorL.stepDown();
                }
                if (_motorR.getAbsSpeed() > 1) {
                    _motorR.stepUp();
                }
            }

            break;

        case CarState::REV_TURN_LEFT :

            break;

        case CarState::REV_TURN_RIGHT :

            _motorR.stepDown();
            if (_motorL.getAbsSpeed() == _motorR.getAbsSpeed()) {
                _state = CarState::REVERSE;
            }
            break;
    }
}

#include "trisonarhandler.h"

#include <wiringPi.h>

TriSonarHandler::TriSonarHandler()
{
    setupPins();
    setupSensors();
}

TriSonarHandler::~TriSonarHandler()
{
    resetPins();
}

void TriSonarHandler::setupPins()
{
    // todo: refactor: move these to the individual sonars.
    pinMode(TRIGGER0, OUTPUT);
    pinMode(ECHO0, INPUT);

    pinMode(TRIGGER1, OUTPUT);
    pinMode(ECHO1, INPUT);

    pinMode(TRIGGER2, OUTPUT);
    pinMode(ECHO2, INPUT);
}

void TriSonarHandler::resetPins()
{
    pinMode(TRIGGER0, INPUT);
    pinMode(TRIGGER1, INPUT);
    pinMode(TRIGGER2, INPUT);
}

void TriSonarHandler::setupSensors()
{

    _sensors.emplace_back(std::make_unique<UltrasonicSensor>(TRIGGER0, ECHO0));
    _sensors.emplace_back(std::make_unique<UltrasonicSensor>(TRIGGER1, ECHO1));
    _sensors.emplace_back(std::make_unique<UltrasonicSensor>(TRIGGER2, ECHO2));
}

std::vector<double> TriSonarHandler::readDistances()
{
    std::vector<double> distances;
    for (unsigned int i = 0; i < NofSonars; ++i) {
        distances.push_back(_sensors[i]->measureDistance());
    }
    return distances;
}

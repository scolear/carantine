#ifndef TRISONARHANDLER_H
#define TRISONARHANDLER_H

#include <vector>
#include <memory>
#include "ultrasonicsensor.h"

#define NofSonars 3

#define TRIGGER0 17
#define ECHO0 16

#define TRIGGER1 27
#define ECHO1 20

#define TRIGGER2 22
#define ECHO2 21

class TriSonarHandler
{
public:
    TriSonarHandler();
    ~TriSonarHandler();

    std::vector<double> readDistances();

private:
    void setupPins();
    void resetPins();
    void setupSensors();

    std::vector<std::unique_ptr<UltrasonicSensor>> _sensors;
};

#endif // TRISONARHANDLER_H

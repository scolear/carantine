#ifndef SENSORWRAPPER_H
#define SENSORWRAPPER_H

#include "ultrasonicsensor.h"
#include <vector>

#define TRIGGER0 17
#define ECHO0 16

#define TRIGGER1 27
#define ECHO1 20

#define TRIGGER2 22
#define ECHO2 21

class SensorWrapper
{
public:
    SensorWrapper();
private:
    std::vector<UltrasonicSensor> _sensors;
};

#endif // SENSORWRAPPER_H

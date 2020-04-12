#include "ultrasonicsensor.h"
#include <chrono>
#include <wiringPi.h>

UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin) : _triggerPin(triggerPin), _echoPin(echoPin) {}

double UltrasonicSensor::measureDistance()
{
    digitalWrite(_triggerPin, 1);
    delayMicroseconds(10);
    digitalWrite(_triggerPin, 0);

    auto startTime = std::chrono::steady_clock::now();
    auto returnTime = std::chrono::steady_clock::now();

    while (digitalRead(_echoPin) == 0) {
        startTime = std::chrono::steady_clock::now();
    }
    while (digitalRead(_echoPin) != 0) {
        returnTime = std::chrono::steady_clock::now();
    }

    std::chrono::duration<double> elapsedTime = returnTime - startTime;

    return (elapsedTime.count() * 34300) / 2;
}

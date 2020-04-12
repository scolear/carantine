#include "ultrasonicsensor.h"
#include <chrono>
#include <iostream>
#include <wiringPi.h>

UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin) : _triggerPin(triggerPin), _echoPin(echoPin) {}

double UltrasonicSensor::measureDistance()
{
    std::cout << "measuring distance..." << std::endl;

    digitalWrite(_triggerPin, 1);
    delay(1);
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
    std::cout << "elapsed time: " << elapsedTime.count() << std::endl;

    return (elapsedTime.count() * 34300) / 2;
}

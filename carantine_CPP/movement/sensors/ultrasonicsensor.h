#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H


class UltrasonicSensor
{
public:
    UltrasonicSensor(int triggerPin, int echoPin);
    double measureDistance();
private:
    int _triggerPin;
    int _echoPin;
};

#endif // ULTRASONICSENSOR_H

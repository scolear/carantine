#include <iostream>
#include <unistd.h>
#include <chrono>
#include <wiringPi.h>

double measureDistance(int triggerPin, int echoPin)
{
    digitalWrite(triggerPin, 1);
    usleep(10);
    digitalWrite(triggerPin, 0);

    auto startTime = chrono::steady_clock::now();
    auto returnTime = chrono::steady_clock::now();

    while (digitalRead(echoPin) == 0) {
        startTime = chrono::steady_clock::now();
    }
    while (digitalRead(echoPin) != 0) {
        returnTime = chrono::steady_clock::now();
    }

    std::chrono::duration<double> elapsedTime = returnTime - startTime;

    return (std::chrono::duration_cast<std::chrono::seconds>elapsedTime.count() * 34300) / 2;

}

int main(void)
{
    wiringPiSetupGpio(void);
    pinMode(17, OUTPUT);
    pinMode(16, INPUT);

    while (true) {
        std::cout << measureDistance(17, 16) << std::endl;
        usleep(1000);
    }

    return 0;
}
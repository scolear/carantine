#include <iostream>
#include <unistd.h>
#include <chrono>
#include <wiringPi.h>

double measureDistance(int triggerPin, int echoPin)
{
    digitalWrite(triggerPin, 1);
    delay(1);
    digitalWrite(triggerPin, 0);

    auto startTime = std::chrono::steady_clock::now();
    auto returnTime = std::chrono::steady_clock::now();

    while (digitalRead(echoPin) == 0) {
        startTime = std::chrono::steady_clock::now();
    }
    while (digitalRead(echoPin) != 0) {
        returnTime = std::chrono::steady_clock::now();
    }

    std::chrono::duration<double> elapsedTime = returnTime - startTime;
    std::cout << "elapsed time: " << elapsedTime.count() << std::endl;

    return (elapsedTime.count() * 34300) / 2;

}

int main()
{
    wiringPiSetupGpio();
    pinMode(17, OUTPUT);
    pinMode(16, INPUT);

    while (true) {
        std::cout << "Distance: " << measureDistance(17, 16) << std::endl;
        delay(1000);
    }

    return 0;
}

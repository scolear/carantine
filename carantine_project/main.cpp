#include <iostream>
#include <wiringPi.h>

#include "movement/trisonarhandler.h"

int main()
{
    wiringPiSetupGpio();

    TriSonarHandler sensors;

    while (true) {

        for (auto distance : sensors.readDistances())
        {
            std::cout << distance << " ";
        }
        std::cout << std::endl;
        delay(1000);
    }
    return 0;
}

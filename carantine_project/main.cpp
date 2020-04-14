#include <iostream>
#include <wiringPi.h>
#include <opencv2/highgui.hpp>

#include "main.h"
#include "movement/trisonarhandler.h"


int main()
{

    wiringPiSetupGpio();

    TriSonarHandler sensors;

    cv::namedWindow("Carantine");
    cv::imshow("Carantine", cv::Mat(100, 100, CV_8UC3, cv::Scalar(0, 0, 0)));

    bool run = true;
    Mode mode = Mode::MANUAL;
    bool displayDistances = true;

    while (run)
    {
        switch (mode) {
            case Mode::MANUAL:
            {
                std::cout << "Manual mode" << std::endl;
                break;
            }
            case Mode::AUTO:
            {
                std::cout << "Auto mode" << std::endl;
                break;
            }
        }

        if (displayDistances)
        {
            for (auto distance : sensors.readDistances())
            {
                std::cout << distance << " ";
            }
            std::cout << std::endl;
        }

        delay(100);

        int c = cv::waitKey(25);
        
        if (c == 'q') {
            run = false;
        } else if (c == 'm') {
            mode = Mode::MANUAL;
        } else if (c == 'a') {
            mode = Mode::AUTO;
        } else if (c == 'd') {
            displayDistances = !displayDistances;
        }
    }

    return 0;
}

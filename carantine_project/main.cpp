#include <iostream>
#include <wiringPi.h>
#include <opencv2/highgui.hpp>

#include "movement/trisonarhandler.h"

int main()
{

    wiringPiSetupGpio();

    TriSonarHandler sensors;

    cv::namedWindow("Carantine");

    bool run = true;

    while (run) {

        for (auto distance : sensors.readDistances())
        {
            std::cout << distance << " ";
        }
        std::cout << std::endl;
        delay(100);

        cv::imshow("Carantine", cv::Mat(100, 100, CV_8UC3, cv::Scalar(0, 0, 0)));

        int c = cv::waitKey(25);
        if (c == 'q')
            break;

    }
    return 0;
}

#include <iostream>
#include <iomanip>

#include <wiringPi.h>
#include <softPwm.h>
#include <opencv2/highgui.hpp>

#include "main.h"
#include "movement/sensors/trisonarhandler.h"
#include "movement/motors/motordriver.h"

int main()
{
    cv::namedWindow("Carantine");
    cv::imshow("Carantine", cv::Mat(100, 100, CV_8UC3, cv::Scalar(0, 0, 0)));

    wiringPiSetupGpio();

    MotorDriver motorDriver(19, 13, 18, 12);

    TriSonarHandler sensors;

    bool run = true;
    Mode mode = Mode::MANUAL;
    bool displayDistances = true;

    while (run)
    {
        int c = cv::waitKey(25);

        switch (c) {
            case 'q':
                run = false;
                std::cout << std::endl << "Exiting" << std::endl;
                break;
            case 'd':
                displayDistances = !displayDistances;
                break;
            case 9 :                                             // TAB
                if (mode == Mode::MANUAL)
                {
                    mode = Mode::AUTO;
                    motorDriver.allStop();

                    std::cout << std::endl << "Auto mode" << std::endl;

                }
                else if (mode == Mode::AUTO)
                {
                    mode = Mode::MANUAL;
                    motorDriver.allStop();

                    std::cout << std::endl << "Manual mode" << std::endl;
                }
                break;
        }

        switch (mode)
        {
            case Mode::MANUAL:
            {
                switch (c)
                {
                    case 32 :                                   // SPACE

                        motorDriver.allStop();

                        std::cout << std::endl << "Stop" << std::endl;
                        break;

                    case 82 :                                   // UP

                        motorDriver.up();

                        std::cout << std::endl << "Up " << std::endl;
                        break;

                    case 84 :                                   // DOWN

                        motorDriver.down();

                        std::cout << std::endl << "Down " << std::endl;
                        break;

                    case 81 :                                   // LEFT

                        motorDriver.left();

                        std::cout << std::endl << "Left" << std::endl;
                        break;

                    case 83 :                                   // RIGHT

                        motorDriver.right();

                        std::cout << std::endl << "Right" << std::endl;
                        break;
                }

                break;
            }
            case Mode::AUTO:
            {
                // Self-driving mode
                break;
            }
        }

        // todo: refactor this out of here
        if (displayDistances)
        {
            std::cout << " \r ";
            for (auto distance : sensors.readDistances())
            {
                std::cout << std::setprecision(4) << std::showpoint << distance << " \t ";
            }
            std::cout << std::flush;
        }

        //delay(100);

    }

    std::cout << std::endl;
    return 0;
}

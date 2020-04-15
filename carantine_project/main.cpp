#include <iostream>
#include <iomanip>

#include <wiringPi.h>
#include <softPwm.h>
#include <opencv2/highgui.hpp>

#include "main.h"
#include "movement/trisonarhandler.h"


int main()
{

    wiringPiSetupGpio();

    pwmSetMode(PWM_MODE_MS);
    pinMode(18, PWM_OUTPUT);
    pinMode(12, OUTPUT);
    digitalWrite(12, 0);

    softPwmCreate (19, 0, 100);
    pinMode(13, OUTPUT);
    digitalWrite(13, 0);
    int speed = 0;

    TriSonarHandler sensors;

    cv::namedWindow("Carantine");
    cv::imshow("Carantine", cv::Mat(100, 100, CV_8UC3, cv::Scalar(0, 0, 0)));

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
            case 9:                                             // TAB
                if (mode == Mode::MANUAL) {
                    mode = Mode::AUTO;
                    std::cout << std::endl << "Auto mode" << std::endl;
                } else if (mode == Mode::AUTO) {
                    mode = Mode::MANUAL;
                    std::cout << std::endl << "Manual mode" << std::endl;
                }
                break;
        }

        switch (mode)
        {
            case Mode::MANUAL:
            {
                // todo:
                switch (c) {
                    case 32 :                                   // SPACE
                        // motor.allStop();
                        //pwmWrite(18, 0);
                        speed = 0;
                        softPwmWrite (19, speed);

                        std::cout << std::endl << "Stop" << std::endl;
                        break;
                    case 82 :                                   // UP
                        // motor.speedUp();
                        //if (speed < 1024 - 50) speed += 50;
                        //pwmWrite(18, speed);
                        if (speed < 100 - 20) speed += 20;
                        softPwmWrite (19, speed);

                        std::cout << std::endl << "Up " << speed << std::endl;
                        break;
                    case 84 :                                   // DOWN
                        // motor.speedDown();
                        //if (speed > 0) speed -= 50;
                        //pwmWrite(18, speed);
                        if (speed > 0) speed -= 20;
                        softPwmWrite (19, speed);

                        std::cout << std::endl << "Down " << speed << std::endl;
                        break;
                    case 81 :                                   // LEFT
                        // motor.leftTurn();
                        std::cout << std::endl << "Left" << std::endl;
                        break;
                    case 83 :                                   // RIGHT
                        // motor.rightTurn();
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

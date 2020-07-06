//
// Created by thijs on 17-10-19.
//

#include <iostream>
#include "Timer.h"

void Timer::start() {
    tStart = cv::getTickCount();
}

void Timer::end() {
    tEnd = cv::getTickCount();
}

void Timer::printSeconds() {
    if (tStart == -1) {
        std::cerr << "No startIndex time set" << std::endl;
    }
    if (tEnd == -1 || tEnd <= tStart) {
        this->end();
    }
    auto t = (double) (tEnd - tStart) / cv::getTickFrequency();
    printTiming("s", t);
    tStart = tEnd;
}

void Timer::printMilliSeconds() {
    if (tStart == -1) {
        std::cerr << "No startIndex time set" << std::endl;
    }
    if (tEnd == -1 || tEnd <= tStart) {
        this->end();
    }
    auto t = (double) (tEnd - tStart) / cv::getTickFrequency();
    printTiming("ms", t*1000.0);
    tStart = tEnd;
}

void Timer::printFPS() {
    frames++;
    if (tStart == -1) {
        std::cerr << "No startIndex time set" << std::endl;
    }
    this->end();
    auto t = (double) (tEnd - tStart) / cv::getTickFrequency();
    if (t > 1) {
        std::cout << name << " per second: " << frames << std::endl;
        tStart = tEnd;
        frames = 0;
    }
}

double Timer::getSeconds(bool print) {
    if (tStart == -1) {
        std::cerr << "No startIndex time set" << std::endl;
    }
    if (tEnd == -1 || tEnd <= tStart) {
        this->end();
    }
    auto t = (double) (tEnd - tStart) / cv::getTickFrequency();
    if (print) {
        printTiming("ms", t*1000.0);
    }
    tStart = tEnd;
    return t;
}

void Timer::printTiming(const std::string &timeScale, double t) {
    if (name == "noName") {
        std::cout << "Time taken: " << t << timeScale << std::endl;
    } else {
        std::cout << name << " taken: " << t << timeScale << std::endl;
    }
}


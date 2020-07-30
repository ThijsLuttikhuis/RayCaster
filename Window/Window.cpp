//
// Created by thijs on 27-12-18.
//

#include "Window.h"
#include "Drawer.h"
#include "../Utils/Timer.h"

namespace window {

std::map<cv::String, cv::Mat> Window::images;

cv::Mat Window::getImage(const cv::String &name) {
    return images[name];
}

int Window::getXPixels(const cv::String &name) {
    return images[name].cols;
}

int Window::getYPixels(const cv::String &name) {
    return images[name].rows;
}

cv::Vec3b Window::getPixel(const cv::String &name,const int &x, const int &y) {
    if (x >= 0 && y >= 0 && x < getXPixels(name) && y < getYPixels(name)) {
        return images[name].at<cv::Vec3b>(y, x);
    }
    else {
        //std::cout << "ERROR: pixel is not within margins." << std::endl;
        return {};
    }
}

void Window::setImage(const cv::String &name, cv::Mat &newImage) {
    images[name] = newImage;
}

bool Window::setPixel(const cv::String &name, const int &x, const int &y, const cv::Vec3b &color) {
    if (x >= 0 && y >= 0 && x < getXPixels(name) && y < getYPixels(name)) {
        images[name].at<cv::Vec3b>(y, x) = color;
        return true;
    }
    return false;
}

void Window::initializeWindow(const cv::String &name, const int &width, const int &height) {
    auto* image = new cv::Mat(height, width, CV_8UC3);
    images[name] = *image;
    cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
    resetWindow(name);
}

int Window::updateWindow(const cv::String &name) {
    cv::imshow(name, images[name]);
    return cv::waitKeyEx(1);
}

void Window::resetWindow(const cv::String &name) {
    images[name] = cv::Mat::zeros(images[name].rows, images[name].cols, CV_8UC3);

}

void Window::moveWindows(const std::vector<cv::String> &names, int startX, int startY, bool nextToEachother) {
    for (auto &name : names) {
        auto imXPixels = getXPixels(name);
        std::cout << name << startX << std::endl;
        cv::moveWindow(name, startX, 20);
        if (nextToEachother) {
            startX += (int)(imXPixels*1.02);
        }
    }
}

} //window
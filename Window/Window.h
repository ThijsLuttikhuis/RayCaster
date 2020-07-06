//
// Created by thijs on 27-12-18.
//

#ifndef FINDBALL_WINDOW_H
#define FINDBALL_WINDOW_H

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <map>

namespace window {

class Window {

    private:
        static std::map<cv::String, cv::Mat> images;
    public:

        static cv::Mat getImage(const cv::String &name);

        static int getXPixels(const cv::String &name);
        static int getYPixels(const cv::String &name);

        static cv::Vec3b getPixel(const cv::String &name, const int &x, const int &y);

        static void setImage(const cv::String &name, cv::Mat &newImage);
        static bool setPixel(const cv::String &name, const int &x, const int &y, const cv::Vec3b &color);

        static void initializeWindow(const cv::String &name, const int &width, const int &height);
        static void resetWindow(const cv::String &name);
        static int updateWindow(const cv::String &name);

};

} //window

#endif //FINDBALL_WINDOW_H

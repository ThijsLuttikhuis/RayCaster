//
// Created by thijs on 27-12-18.
//

#ifndef SOLARSYSTEM_DRAWER_H
#define SOLARSYSTEM_DRAWER_H

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "Window.h"
#include <memory>

namespace window {

class Drawer {
private:

public:
    static void drawRectangle(const cv::String &name,
          const int &xLeftBottom, const int &yLeftBottom, const int &width, const int &height, const cv::Vec3b &color);

    static void drawCircle(const cv::String &name,
          const int &xCenter, const int &yCenter, double radius, const cv::Vec3b &color);

    static void drawCircle(const cv::String &name,
          const double &xCenter, const double &yCenter, double innerRadius, double outerRadius, const cv::Vec3b &color);

    static void drawLineSegment(const cv::String &name,
          const double &xStart, const double &yStart, const double &xEnd, const double &yEnd, const cv::Vec3b &color);

    static void drawLineSegment(const cv::String &name,
          const double &xStart, const double &yStart, const double &angle, const cv::Vec3b &color);

    static void drawDottedLineSegment(const cv::String &name,
                                const double &xStart, const double &yStart, const double &xEnd, const double &yEnd, const cv::Vec3b &color);

    static void drawDottedLineSegment(const cv::String &name,
                                const double &xStart, const double &yStart, const double &angle, const cv::Vec3b &color);

    static void drawPixel(const cv::String &name,
          const int &x, const int &y, const cv::Vec3b &color);

};

} //window

#endif //SOLARSYSTEM_DRAWER_H


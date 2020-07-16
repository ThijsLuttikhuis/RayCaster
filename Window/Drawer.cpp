//
// Created by thijs on 27-12-18.
//

#include "Drawer.h"

namespace window {




void Drawer::drawRectangle(const cv::String &name, const int &xLeftBottom, const int &yLeftBottom, const int &width,
                           const int &height, const cv::Vec3b &color) {

    for (int x = xLeftBottom; x < xLeftBottom+width; x++) {
        for (int y = yLeftBottom; y < yLeftBottom+height; y++) {
            Window::setPixel(name, x, y, color);
        }
    }
}

void Drawer::drawCircle(const cv::String &name,
      const int &xCenter, const int &yCenter, double radius, const cv::Vec3b &color) {

    int pixels = Window::getXPixels(name) > Window::getYPixels(name) ?
          Window::getYPixels(name) : Window::getXPixels(name);

    if (xCenter < 0 || xCenter > Window::getXPixels(name) || yCenter < 0 || yCenter > Window::getYPixels(name)) {
        return;
    }

    if (radius < 4.0 || radius < pixels * 0.005) {
        double inner = pixels * 0.010;
        double outer = (pixels * 0.002 > 1.0 ? pixels * 0.012 : pixels * 0.010 + 1.0);
        drawCircle(name, xCenter, yCenter, inner, outer, color);
    }
    double radiusSquared = radius * radius;
    for (int x = static_cast<int>(round(xCenter - radius)); x < round(xCenter + radius); x++) {
        for (int y = static_cast<int>(round(yCenter - radius)); y < round(yCenter + radius); y++) {
            double dx = x - xCenter;
            double dy = y - yCenter;
            if (dx * dx + dy * dy < radiusSquared) {
                Window::setPixel(name, x, y, color);
            }
        }
    }
}

void Drawer::drawCircle(const cv::String &name,
      const double &xCenter, const double &yCenter, double innerRadius, double outerRadius,const cv::Vec3b &color) {

    double outerRadiusSquared = outerRadius * outerRadius;
    double innerRadiusSquared = innerRadius * innerRadius;
    for (int x = static_cast<int>(round(xCenter - outerRadius)); x < round(xCenter + outerRadius); x++) {
        for (int y = static_cast<int>(round(yCenter - outerRadius)); y < round(yCenter + outerRadius); y++) {
            double dx = x - xCenter;
            double dy = y - yCenter;
            if (dx * dx + dy * dy < outerRadiusSquared && dx * dx + dy * dy > innerRadiusSquared) {
                Window::setPixel(name, x, y, color);
            }
        }
    }
}

void Drawer::drawLineSegment(const cv::String &name,
      const double &xStart, const double &yStart, const double &xEnd, const double &yEnd, const cv::Vec3b &color) {

    double xA = xEnd - xStart;
    double yA = yEnd - yStart;
    if (abs(xA) > abs(yA)) {
        double a = yA / xA;
        double b = yStart - a * xStart;

        auto x = std::min((int)xStart, (int)xEnd);
        auto xM = std::max((int)xStart, (int)xEnd);
        for (; x < xM; x++) {
            auto yy = (int)round(x * a + b);
            Window::setPixel(name, x, yy, color);
        }
    }
    else {
        double a =  xA / yA;
        double b = xStart - a * yStart;

        auto y = std::min((int)yStart, (int)yEnd);
        auto yM = std::max((int)yStart, (int)yEnd);
        for (; y < yM; y++) {
            auto xx = (int)round(y * a + b);
            Window::setPixel(name, xx, y, color);
        }
    }
}

void Drawer::drawLineSegment(const cv::String &name,
      const double &xStart, const double &yStart, const double &angle, const cv::Vec3b &color) {

    double length = std::max(Window::getYPixels(name), Window::getXPixels(name));

    double xEnd = xStart + sin(angle*M_PI/180.0) * length;
    double yEnd = yStart + cos(angle*M_PI/180.0) * length;

    drawLineSegment(name, xStart, yStart, xEnd, yEnd, color);
}

void Drawer::drawPixel(const cv::String &name, const int &x, const int &y, const cv::Vec3b &color) {
    if (x < 0 || x > Window::getXPixels(name) || y < 0 || y > Window::getYPixels(name)) {
        std::cerr << "setting pixel outside image with coordinate x = " << x << " and y = " << y << "." << std::endl;
        return;
    }
    Window::setPixel(name,x,y,color);
}

} //window
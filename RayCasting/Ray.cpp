//
// Created by thijs on 01-07-20.
//

#include "Ray.h"
#include "../Window/Drawer.h"
#include "../Utils/Utilities.h"

void rc::Ray::drawTopDown(const cv::String &name) {
    window::Drawer::drawLineSegment(name, position.x, position.y, end.x, end.y, {255,255,255});
}

void rc::Ray::drawTopDown(const cv::String &name, const Position &endPoint) {
    window::Drawer::drawLineSegment(name, position.x, position.y, endPoint.x, endPoint.y, {255,255,255});
}

void rc::Ray::calculateCollision(const cv::String &name, World &walls, const double &viewDistance) {
    walls.sortWalls(position);

    resetEnd(name, viewDistance);
    for (auto &wall : walls.getWalls()) {
        Position newEnd = lineSegmentIntersection(position, end, wall.start, wall.end);
        if (newEnd != Position()) {
            end = newEnd;
            break;
        }
    }
}

void rc::Ray::resetEnd(const cv::String &name, const double &viewDistance) {
    double xEnd = position.x + sin(angle.getAngleRad()) * viewDistance;
    double yEnd = position.y + cos(angle.getAngleRad()) * viewDistance;
    end = Position(xEnd, yEnd);
}

void rc::Ray::draw3D(const cv::String &name, int xLeft, int width) {
    double distance = position.distance(end);
    int xPixels = window::Window::getXPixels(name);
    int yPixels = window::Window::getYPixels(name);

    int smallestDim = std::min(xPixels, yPixels);

    // out of range
    if (distance > smallestDim*0.95) {
        return;
    }

    // distance at which the wall covers the whole screen
    double distanceAtFullHeight = 3.0 * window::Window::getYPixels(name);

    // redundant pixel drawing
    if (abs(distance) > distanceAtFullHeight * yPixels * 0.5) {
        distance = distanceAtFullHeight * yPixels * 0.5;
    }

    int yBottom = static_cast<int>(0.5 * yPixels - distanceAtFullHeight/distance);
    int height = static_cast<int>(distanceAtFullHeight*2.0/distance);
    window::Drawer::drawRectangle(name, xLeft, yBottom, width, height, {255,255,255});
}

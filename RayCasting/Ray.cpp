//
// Created by thijs on 01-07-20.
//

#include "Ray.h"
#include "../Window/Drawer.h"
#include "../Utils/Utilities.h"

void rc::Ray::drawTopDown(const cv::String &name, const Position &centerPoint) {

    window::Drawer::drawLineSegment(name, centerPoint.x, centerPoint.y,
          centerPoint.x - position.x + wallIntersect.location.x,
          centerPoint.y - position.y + wallIntersect.location.y,
          {255,255,255});
}

void rc::Ray::calculateCollision(const cv::String &name, World &walls, const double &viewDistance) {
    walls.sortWalls(position);

    resetEnd(name, viewDistance);
    for (auto &wall : walls.getWalls()) {
        Position newEnd = lineSegmentIntersection(position, wallIntersect.location, wall.start, wall.end);
        if (newEnd != Position()) {
            wallIntersect.location = newEnd;
            wallIntersect.wallHeight = wall.height;
            wallIntersect.wallTexture = wall.type;
            break;
        }
    }
}

void rc::Ray::resetEnd(const cv::String &name, const double &viewDistance) {
    double xEnd = position.x + sin(angle.getAngleRad()) * viewDistance;
    double yEnd = position.y + cos(angle.getAngleRad()) * viewDistance;
    wallIntersect.location = Position(xEnd, yEnd);
    wallIntersect.wallTexture = "";
    wallIntersect.wallHeight = 0.0;
}

void rc::Ray::draw3D(const cv::String &name, int xLeft, int width, const double &fovHorizontal) {

    double horizontalDistance = position.distance(wallIntersect.location);

    double playerHeight = 180;                          // cm

    if (wallIntersect.wallHeight == 0.0 || wallIntersect.wallTexture.empty()) {
        return;
    }

    double wallBottom = - playerHeight;
    double wallTop = wallIntersect.wallHeight - playerHeight;

    int yPixels = window::Window::getYPixels(name);
    int xPixels = window::Window::getXPixels(name);

    double fovVertical = fovHorizontal * yPixels / xPixels;
    double fovVerticalRad = fovVertical * M_PI / 180;
    double verticalDistance = horizontalDistance*tan(0.5*fovVerticalRad);

    int bottomDrawHeight = static_cast<int>(yPixels * (0.5*wallBottom/verticalDistance + 0.5));
    int topDrawHeight = static_cast<int>(yPixels * (0.5*wallTop/verticalDistance + 0.5));

    bottomDrawHeight = bottomDrawHeight < 0 ? 0 : bottomDrawHeight;
    topDrawHeight = topDrawHeight > yPixels ? yPixels : topDrawHeight;

    window::Drawer::drawRectangle(name, xLeft, bottomDrawHeight,
          width, topDrawHeight - bottomDrawHeight, {255,255,255});
}

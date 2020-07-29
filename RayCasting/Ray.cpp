//
// Created by thijs on 01-07-20.
//

#include "Ray.h"
#include "../Window/Drawer.h"
#include "../Utils/Utilities.h"
#include "Texture.h"

void rc::Ray::drawTopDown(const cv::String &name, const Position &centerPoint, const double &zoomFactor) {

    window::Drawer::drawLineSegment(name, centerPoint.x, centerPoint.y,
          centerPoint.x + (wallIntersect.location.x - position.x)*zoomFactor,
          centerPoint.y + (wallIntersect.location.y - position.y)*zoomFactor,
          {255,255,255});
}

void rc::Ray::calculateCollision(const cv::String &name, World &walls, const double &viewDistance) {
    resetEnd(name, viewDistance);
    for (auto &wall : walls.getWalls()) {
        Position newEnd = lineSegmentIntersection(position, wallIntersect.location, wall.start, wall.end);
        if (newEnd != Position()) {
            wallIntersect.location = newEnd;
            wallIntersect.wallHeight = wall.height;
            wallIntersect.wallTexture = wall.type;
            wallIntersect.wallSection = newEnd.distance(wall.start);
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

    double playerHeight = 180;          // cm

    if (wallIntersect.wallHeight == 0.0 || wallIntersect.wallTexture.empty()) {
        return;
    }

    double wallBottom = playerHeight;
    double wallTop = playerHeight - wallIntersect.wallHeight;

    int yPixels = window::Window::getYPixels(name);
    int xPixels = window::Window::getXPixels(name);

    double fovVertical = fovHorizontal * yPixels / xPixels;
    double fovVerticalRad = deg2Rad(fovVertical);
    double verticalDistance = horizontalDistance*tan(0.5*fovVerticalRad);

    int bottomDrawHeight = static_cast<int>(yPixels * (0.5*wallBottom/verticalDistance + 0.5));
    int topDrawHeight = static_cast<int>(yPixels * (0.5*wallTop/verticalDistance + 0.5));

    int realBottom = bottomDrawHeight;
    int realTop = topDrawHeight;
    bottomDrawHeight = bottomDrawHeight > yPixels ? yPixels : bottomDrawHeight;
    topDrawHeight = topDrawHeight < 0 ? 0 : topDrawHeight;

    window::Texture::drawTexture(name, wallIntersect.wallTexture, xLeft, bottomDrawHeight,
          topDrawHeight, realBottom, realTop, wallIntersect.wallSection, wallIntersect.wallHeight);
}

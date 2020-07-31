//
// Created by thijs on 01-07-20.
//

#include "Ray.h"
#include "../Window/Drawer.h"
#include "../Utils/Utilities.h"
#include "Texture.h"
#include <list>

void rc::Ray::drawTopDown(const cv::String &name, const Position &centerPoint, const double &zoomFactor) {

    window::Drawer::drawLineSegment(name, centerPoint.x, centerPoint.y,
                                    centerPoint.x + (wallIntersections[0].location.x - position.x) * zoomFactor,
                                    centerPoint.y + (wallIntersections[0].location.y - position.y) * zoomFactor,
                                    {255, 255, 255});
}

void rc::Ray::calculateCollision(const cv::String &name, World &walls, const double &viewDistance) {
    resetEnd(name, viewDistance);
    for (auto &wall : walls.getWalls()) {
        Position newEnd = lineSegmentIntersection(position, wallIntersections[0].location, wall.start, wall.end);
        if (newEnd != Position()) {
            WallIntersection wallIntersection;
            wallIntersection.location = newEnd;
            wallIntersection.wallBot = wall.bot;
            wallIntersection.wallTop = wall.top;
            wallIntersection.wallTexture = wall.type;
            wallIntersection.wallSection = newEnd.distance(wall.start);
            wallIntersections.push_back(wallIntersection);
        }
    }
}

void rc::Ray::resetEnd(const cv::String &name, const double &viewDistance) {

    WallIntersection wallIntersection;
    double xEnd = position.x + sin(angle.getAngleRad()) * viewDistance;
    double yEnd = position.y + cos(angle.getAngleRad()) * viewDistance;
    wallIntersection.location = Position(xEnd, yEnd);
    wallIntersection.wallTexture = "";
    wallIntersection.wallBot = 0.0;
    wallIntersection.wallTop = 0.0;

    wallIntersections.clear();
    wallIntersections.push_back(wallIntersection);
}

void rc::Ray::draw3D(const cv::String &name, int xLeft, int width, const double &fovHorizontal) {
    // vector that keeps track of parts of the screen that have been drawn already
    std::list<std::pair<int, int>> ignorePixels;

    // loop over all walls
    for (auto &wallIntersection : wallIntersections) {

        // ignore empty walls
        if (wallIntersection.wallBot >= wallIntersection.wallTop || wallIntersection.wallTexture.empty()) {
            continue;
        }

        // get window pixels
        int yPixels = window::Window::getYPixels(name);
        int xPixels = window::Window::getXPixels(name);

        // distance to wall
        double horizontalDistance = position.distance(wallIntersection.location);

        // wall heights relative to player
        double playerHeight = 180;          // cm
        double wallBottom = playerHeight - wallIntersection.wallBot;
        double wallTop = playerHeight - wallIntersection.wallTop;

        // calculate vertical view range at the horizontal distance
        double fovVertical = fovHorizontal * yPixels / xPixels;
        double fovVerticalRad = deg2Rad(fovVertical);
        double verticalDistance = horizontalDistance * tan(0.5 * fovVerticalRad);

        // calculate the range of y-pixels to draw
        int bottomDrawHeight = static_cast<int>(yPixels * (0.5 * wallBottom / verticalDistance + 0.5));
        int topDrawHeight = static_cast<int>(yPixels * (0.5 * wallTop / verticalDistance + 0.5));

        // draw texture
        window::Texture::drawTexture(name, wallIntersection.wallTexture, xLeft, bottomDrawHeight,
                                     topDrawHeight, wallIntersection.wallSection,
                                     wallIntersection.wallBot, wallIntersection.wallTop, ignorePixels);
    }
}

void rc::Ray::sortCollisionsByDistance(bool furthestFirst) {
    std::sort(wallIntersections.begin(), wallIntersections.end(),
              [this, furthestFirst](const WallIntersection &a, const WallIntersection &b) {

        return furthestFirst ? a.location.distance2(position) < b.location.distance2(position)
                             : a.location.distance2(position) > b.location.distance2(position);
    });
}

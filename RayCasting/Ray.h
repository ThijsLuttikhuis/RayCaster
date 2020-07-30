//
// Created by thijs on 01-07-20.
//

#ifndef RAYCASTER_RAY_H
#define RAYCASTER_RAY_H


#include <opencv2/core/cvstd.hpp>
#include "../Utils/Position.h"
#include "../Utils/Angle.h"
#include "World.h"

namespace rc { //raycasting

class WallIntersection {
public:
    Position location;
    double wallBot;
    double wallTop;
    std::string wallTexture;
    double wallSection;

    WallIntersection() = default;
};

class Ray {
private:
    Position position;
    std::vector<WallIntersection> wallIntersections;
    Angle angle;

public:
    Ray(Position position, Angle angle) : position(position), angle(angle) { };

    void drawTopDown(const cv::String &name, const Position &centerPoint, const double &zoomFactor);

    void draw3D(const cv::String &name, int xLeft, int width, const double &fovHorizonal);

    void calculateCollision(const cv::String &name, World &walls, const double &viewDistance);

    void sortCollisionsByDistance(bool furthestFirst = false);

    void resetEnd(const cv::String &name, const double &viewDistance);
};

} //rc

#endif //RAYCASTER_RAY_H

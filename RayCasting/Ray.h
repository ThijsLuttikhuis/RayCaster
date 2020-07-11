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

class WallIntersect {
public:
    Position location;
    double wallHeight;
    std::string wallTexture;
};

class Ray {
private:
    Position position;
    WallIntersect wallIntersect;
    Angle angle;

public:
    Ray(Position position, Angle angle) : position(position), angle(angle) { };

    void drawTopDown(const cv::String &name, const Position &centerPoint);
    void draw3D(const cv::String &name, int xLeft, int width, const double &fovHorizonal);

    void calculateCollision(const cv::String &name, World &walls, const double &viewDistance);

    void resetEnd(const cv::String &name, const double &viewDistance);
};

} //rc

#endif //RAYCASTER_RAY_H

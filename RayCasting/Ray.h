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

class Ray {
private:
    Position position;
    Position end;
    Angle angle;


public:
    Ray(Position position, Angle angle) : position(position), angle(angle) { };

    void drawTopDown(const cv::String &name);
    void drawTopDown(const cv::String &name, const Position &end);
    void draw3D(const cv::String &name, int xLeft, int width);

    void calculateCollision(const cv::String &name, World &walls);

    void resetEnd(const cv::String &name);
};

} //rc

#endif //RAYCASTER_RAY_H

//
// Created by thijs on 04-07-20.
//

#ifndef RAYCASTER_WALL_H
#define RAYCASTER_WALL_H


#include <string>
#include <utility>
#include <opencv2/core/cvstd.hpp>
#include "../Utils/Position.h"

class Wall {
public:
    std::string type;
    Position start;
    Position end;

    void drawTopDown(const cv::String &name);

    Wall() : type(""), start(), end() { };
    Wall(std::string type, const Position &start, const Position &end) :
        type(std::move(type)), start(start), end(end) { };
};


#endif //RAYCASTER_WALL_H

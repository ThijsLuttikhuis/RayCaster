//
// Created by thijs on 04-07-20.
//

#ifndef RAYCASTER_WORLD_H
#define RAYCASTER_WORLD_H


#include <vector>
#include <string>
#include "Wall.h"
#include "../Utils/Position.h"

class Player;

class World {
private:
    std::vector<Wall> walls;
public:
    World() = default;

    bool getWallsFromFile(const std::string &filename);

    [[nodiscard]] const std::vector<Wall> &getWalls() const;
    void sortWalls(const Position &pos);
    void drawWallsTopDown(const cv::String &name, const Player &player);
};


#endif //RAYCASTER_WORLD_H

//
// Created by thijs on 04-07-20.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include "World.h"
#include "../Utils/Utilities.h"

bool World::getWallsFromFile(const std::string &fileName) {
    walls.clear();

    std::string line;
    std::string data;
    std::ifstream myfile(fileName);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (line.empty()) {
                continue;
            }
            std::vector<std::string> parsedLine;
            split(line, parsedLine, ',');
            char comment = '#';
            if ((int)parsedLine[0][0] == (int)comment) {
                continue;
            }
            Wall wall;
            wall.type = parsedLine[0];
            wall.start = {std::stod(parsedLine[1]), std::stod(parsedLine[2])};
            wall.end = {std::stod(parsedLine[3]), std::stod(parsedLine[4])};
            walls.push_back(wall);
        }
        myfile.close();
        return true;
    } else {
        std::cerr << "Unable to open file";
    }
    return false;
}

void World::drawWallsTopDown(const cv::String &name) {
    for (auto &wall : walls) {
        wall.drawTopDown(name);
    }
}

const std::vector<Wall> &World::getWalls() const {
    return walls;
}

void World::sortWalls(const Position &pos) {
    std::sort(std::begin(walls), std::end(walls), [pos](const Wall &a, const Wall &b) {
        double aDistance = distanceLineSegmentToPoint(a.start, a.end, pos);
        double bDistance = distanceLineSegmentToPoint(b.start, b.end, pos);
        if (std::abs(aDistance - bDistance) < 0.1) {
            return distanceLineToPoint(a.start, a.end, pos) > distanceLineToPoint(b.start, b.end, pos);
        }
        else {
            return aDistance < bDistance;
        }
    });
}





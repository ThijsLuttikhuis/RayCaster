//
// Created by thijs on 04-07-20.
//

#include "Wall.h"
#include "../Window/Drawer.h"


void Wall::drawTopDown(const cv::String &name) {
    window::Drawer::drawLineSegment(name, start.x, start.y, end.x, end.y, {255,0,0});
}

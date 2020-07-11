//
// Created by thijs on 04-07-20.
//

#include "Wall.h"
#include "../Window/Drawer.h"


void Wall::drawTopDown(const cv::String &name, const Position &centerOfScreen) {

    window::Drawer::drawLineSegment(name, start.x - centerOfScreen.x, start.y  - centerOfScreen.y,
          end.x  - centerOfScreen.x, end.y  - centerOfScreen.y, {255,0,0});
}

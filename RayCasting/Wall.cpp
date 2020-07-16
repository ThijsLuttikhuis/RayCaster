//
// Created by thijs on 04-07-20.
//

#include "Wall.h"
#include "../Window/Drawer.h"
#include "Player.h"

void Wall::drawTopDown(const cv::String &name, const Position &centerOfScreen, const Player &player) {
    const double &zoomFactor = player.getZoomTopDown();
    const Position &position = player.getPosition();
    window::Drawer::drawLineSegment(name,
          centerOfScreen.x + (start.x - position.x) * zoomFactor,
          centerOfScreen.y + (start.y - position.y) * zoomFactor,
          centerOfScreen.x + (end.x - position.x) * zoomFactor,
           centerOfScreen.y + (end.y - position.y) * zoomFactor,
           {255,0,0});
}

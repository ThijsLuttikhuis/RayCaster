//
// Created by thijs on 02-07-20.
//

#ifndef RAYCASTER_PLAYER_H
#define RAYCASTER_PLAYER_H


#include <vector>
#include "../Utils/Position.h"
#include "../Utils/Angle.h"
#include "Ray.h"
#include "../Utils/Timer.h"

class World;
struct ThreadArgs {
public:
    cv::String name;
    int startIndex;
    int endIndex;
    int xPixels;
    int size;
};

class Player {
private:
    Position position;
    Angle lookDirection;
    double fovHorizontal;
    int resolution360;
    double moveSpeed = 800;         // cm/s
    double rotateSpeed = 360;       // deg/s
    double viewdistance = 20000;    // cm

    double zoomFactor = 1;
    std::vector<rc::Ray> rays;

    void* drawRays3DThread(void* arg);

public:
    Player(Position position, Angle lookDirection, double fieldOfView, int resolution360) :
          position(position), lookDirection(lookDirection),
          fovHorizontal(fieldOfView), resolution360(resolution360) {};

    void move(double dt, int key);
    void createRays();
    void calculateCollisions(const cv::String &name, World &world);

    [[nodiscard]] const Position &getPosition() const;

    void drawRaysTopDown(const cv::String &name);
    void drawRays3D(const cv::String &name);

    void zoomTopDown(int key);
    void setZoomTopDown(double zoom);
    const double &getZoomTopDown() const;

};




#endif //RAYCASTER_PLAYER_H

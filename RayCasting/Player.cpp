//
// Created by thijs on 02-07-20.
//

#include <thread>
#include "Player.h"
#include "../Window/Drawer.h"

void Player::createRays() {
    rays.clear();
    double fov_2 = fovHorizontal / 2.0;
    Angle aS = lookDirection - fov_2;
    double fovCounter = 0.0;

    while (fovCounter < fovHorizontal) {
        Angle rA = aS + fovCounter;
        rc::Ray ray = rc::Ray(position, rA);
        rays.push_back(ray);
        fovCounter += 360.0/resolution360;
    }
}

void Player::drawRaysTopDown(const cv::String &name){
    Position centerOfScreen = {0.5*window::Window::getXPixels(name), 0.5*window::Window::getYPixels(name)};
    int maxDrawnRays = 20;
    int size = rays.size();
    double skip = 0;
    if (size > maxDrawnRays) {
        skip = (double)size / maxDrawnRays;
    }
    double count = 0.0;
    for (auto &ray : rays) {
        if ((count+=1) > skip) {
            count -= skip;
            ray.drawTopDown(name, centerOfScreen);
        }
    }
    window::Drawer::drawCircle(name, centerOfScreen.x, centerOfScreen.y,
          3, 5, {255,255,255});
}

void Player::drawRays3D(const cv::String &name) {
    int nThreads = 8;
    int xPixels = window::Window::getXPixels(name);
    int size = rays.size();

    if (nThreads > 1) {
        // Init Thread arguments
        ThreadArgs targ[nThreads];
        std::thread tid[nThreads];

        for (int n = 0; n < nThreads; n++) {
            targ[n].name = name;
            targ[n].startIndex = n * size / nThreads;
            targ[n].endIndex = (n + 1) * size / nThreads;
            targ[n].size = size;
            targ[n].xPixels = xPixels;

            tid[n] = std::thread(&Player::drawRays3DThread, this, &targ[n]);
        }

        for (int n = 0; n < nThreads; n++) {
            tid[n].join();
        }

    } else {
        ThreadArgs targ{};
        targ.name = name;
        targ.startIndex = 0;
        targ.endIndex = size;
        targ.size = size;
        targ.xPixels = xPixels;

        drawRays3DThread(&targ);
    }
}


void* Player::drawRays3DThread(void* arg) {
    // Get Thread Arguments
    ThreadArgs threadArgs = *(ThreadArgs*) arg;
    cv::String &name = threadArgs.name;
    int &startIndex = threadArgs.startIndex;
    int &endIndex = threadArgs.endIndex;
    int &xPixels = threadArgs.xPixels;
    int &size = threadArgs.size;

    for (unsigned long i = startIndex; i < endIndex; i++) {
        int xLeft = static_cast<int>(xPixels * (size-i-1) / size);
        int width = static_cast<int>(xPixels/size);
        rays[i].draw3D(name, xLeft, width, fovHorizontal);
    }

    return nullptr;
}

void Player::move(double dt, int key) {
    Angle moveDirection;
    int rot = 0;
    switch(key) {
        case FORWARDS:
            moveDirection = lookDirection;
            break;
        case BACKWARD:
            moveDirection = lookDirection + 180;
            break;
        case LEFT:
            moveDirection = lookDirection + 90;
            break;
        case RIGHT:
            moveDirection = lookDirection + 270;
            break;
        case ROT_LEFT:
            rot = 1;
            break;
        case ROT_RIGHT:
            rot = -1;
            break;
        default:
            return;
    }

    // minimum 50 physics steps
    if (dt > 0.02) {
        dt = 0.02;
    }

    if (moveDirection.isSet()) {
        position.x += sin(moveDirection.getAngleRad()) * dt * moveSpeed;
        position.y += cos(moveDirection.getAngleRad()) * dt * moveSpeed;
    }
    lookDirection = lookDirection + rot * dt * rotateSpeed;
}

void Player::calculateCollisions(const cv::String &name, World &world) {
    for (auto &ray : rays) {
        ray.calculateCollision(name, world, viewdistance);
    }
}

const Position &Player::getPosition() const {
    return position;
}



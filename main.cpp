//
// Created by thijs on 27-12-18.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "Window/Window.h"
#include "Window/Drawer.h"
#include "Utils/Timer.h"
#include "RayCasting/Player.h"
#include "RayCasting/Ray.h"

int main() {
    // init 3D Window
    cv::String windowName3D = "Raycaster 3D View";
    window::Window::initializeWindow(windowName3D, 1024, 768);

    // init Top Down Window
    cv::String windowNameTopDown = "Raycaster Top Down View";
    window::Window::initializeWindow(windowNameTopDown, 512, 768);

    // init World
    World world;
    world.getWallsFromFile("./../walls.txt");

    // init Player
    Player player = Player({0, 0}, Angle(120), 120, 1440);

    // init Timer
    Timer timer;
    timer.start();

    Timer timerDraw3D("3D Draw Time");
    timerDraw3D.start();

    Timer timerDrawTopDown("Top Down Draw Time");
    timerDrawTopDown.start();

    // game Loop
    while(true) {
        double t = timer.getSeconds(true);
        int key = window::Window::updateWindow(windowNameTopDown);
        window::Window::updateWindow(windowName3D);

        // reset Window
        window::Window::resetWindow(windowNameTopDown);
        window::Window::resetWindow(windowName3D);

        // check Exit
        if (key==27) {
            return 0;
        }

        // move Player
        player.move(t, key);

        // create/collide Rays
        player.createRays();
        player.calculateCollisions(windowNameTopDown, world);

        // draw Top Down
        timerDrawTopDown.start();
        player.drawRaysTopDown(windowNameTopDown);
        world.drawWallsTopDown(windowNameTopDown);
        timerDrawTopDown.printMilliSeconds();

        // draw 3D
        timerDraw3D.start();
        player.drawRays3D(windowName3D);
        timerDraw3D.printMilliSeconds();
    }
}
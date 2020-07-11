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

//#define PRINT_TIMING
#define PRINT_KEY_PRESS

int main() {

    // init Top Down Window
    cv::String windowNameTopDown = "Raycaster Top Down View";
    window::Window::initializeWindow(windowNameTopDown, 512, 768);

    // init 3D Window
    cv::String windowName3D = "Raycaster 3D View";
    window::Window::initializeWindow(windowName3D, 1024, 768);

    // move Windows
    cv::waitKeyEx(1);
    window::Window::moveWindows({windowName3D,windowNameTopDown}, 100,100,true);

    // init World
    World world;
    world.getWallsFromFile("./../walls.txt");

    // init Player
    Player player = Player({400, 500}, Angle(0), 90, 1440);

    // init Timer
    Timer timer;
    timer.start();

    Timer timerDraw3D("3D Draw Time");
    timerDraw3D.start();

    Timer timerDrawTopDown("Top Down Draw Time");
    timerDrawTopDown.start();

    bool printTotalTime = false;
#ifdef PRINT_TIMING
    printTotalTime = true;
#endif

    // game Loop
    while(true) {

        double t = timer.getSeconds(printTotalTime);

        int key = window::Window::updateWindow(windowNameTopDown);
#ifdef PRINT_KEY_PRESS
        std::cout << "key: " << key << std::endl;
#endif

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
#ifdef PRINT_TIMING
        timerDrawTopDown.start();
#endif
        player.drawRaysTopDown(windowNameTopDown);
        world.drawWallsTopDown(windowNameTopDown, player.getPosition());
#ifdef PRINT_TIMING
        timerDrawTopDown.printMilliSeconds();
#endif

        // draw 3D
#ifdef PRINT_TIMING
        timerDraw3D.start();
#endif
        player.drawRays3D(windowName3D);
#ifdef PRINT_TIMING
        timerDraw3D.printMilliSeconds();
#endif
    }
}
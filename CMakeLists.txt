cmake_minimum_required(VERSION 3.14)
project(RayCaster)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -O3")

find_package( OpenCV REQUIRED )
find_package( Threads REQUIRED )

add_executable(RayCaster main.cpp
        RayCasting/Ray.cpp RayCasting/Ray.h Utils/Position.cpp Utils/Position.h Utils/Angle.cpp Utils/Angle.h
        Window/Drawer.cpp Window/Drawer.h Window/Window.cpp Window/Window.h
        RayCasting/Player.cpp RayCasting/Player.h Utils/Timer.h Utils/Timer.cpp RayCasting/World.cpp RayCasting/World.h RayCasting/Wall.cpp RayCasting/Wall.h Utils/Utilities.h RayCasting/Texture.cpp RayCasting/Texture.h)

target_link_libraries( RayCaster
        ${OpenCV_LIBS}
        ${CMAKE_THREAD_LIBS_INIT}
        )

cmake_minimum_required(VERSION 3.0)

# project(X-TOUCH C)
project (X-TOUCH)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -lasound") # -Wall
set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/LCM/lcm-1.4.0/lcm)
include_directories(${CMAKE_SOURCE_DIR}/LCM/XTouchMsg)

link_directories(/usr/lib/x86_64-linux-gnu/gedit/plugins) # search for alsa
link_directories(${CMAKE_SOURCE_DIR}/LCM/build) # search for LCM
# add_executable(XTOUCH src/DJcontrollerLCM.c)
# target_link_libraries(XTOUCH asound m time)

add_executable(XTOUCH main.cpp src/XTouch.cpp src/Fader.cpp src/ControlParameters.cpp)
target_link_libraries(XTOUCH asound m time lcm)

add_executable(lcm_test ./src/lcm_test.cpp)
target_link_libraries(lcm_test lcm)
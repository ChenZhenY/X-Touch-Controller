/*
 * @file main.cpp
 * @brief: setting up the functions in new framework. Parameters should be independent
 * to XTouch class.
 */

#include "XTouch.hpp"
#include "ControlParameters.hpp"

int main(int argc, char *argv[]) {

    XTouch tuner;
    ControlParameters Kp("Kp", 0, 100);

    tuner.fader0.param = &Kp;
}
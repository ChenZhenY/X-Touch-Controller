/*
 * @file main.cpp
 * @brief: setting up the functions in new framework. Parameters should be independent
 * to XTouch class.
 */

#include "XTouch.hpp"

int main(int argc, char *argv[]) {

    XTouch Xcontroller;

    ControlParameters Kp("Kp", 0, 1001);
    ControlParameters Ki("Ki", -6, 6);
    ControlParameters Kd("Kd", 0, 101);
    ControlParameters om("omega", 0, 10010);
    ControlParameters th("theta", -10, 1001);
    ControlParameters la("lambda", 0, 1001);
    ControlParameters ca("lda", 0, 1001);
    ControlParameters cd("la", 0, 1001);
    ControlParameters we("lamd", 0, 1001);

    // control param assigned to 9 channel
    vector<ControlParameters*> fader_param_map = {&Kp, &Ki, &Kd, &om, &th, &la, &ca, &cd, &we}; 

    for (int i=0; i<9; i++) {
        Xcontroller.fader[i].param = fader_param_map[i];
    }
    
    int status = -1;
    while (true) {
        status = Xcontroller.update();
    }
    
}
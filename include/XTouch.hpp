/*!
 * @file XTouch.hpp
 * @brief define all the members and functionalities of XTouch controller.
 * read from XTouch using alsa MIDI under Mackie Control. Send data to RS.
 * display result on LCD display.
 * @TODO: wrap up parameters in file or change using LCM
 */

#ifndef XTOUCH
#define XTOUCH

#include <fstream>
#include <iostream>

#include <alsa/asoundlib.h>
#include <math.h>
#include <time.h>

#include "Fader.hpp"
// #include <Rotator.hpp>
// #include <Button.hpp>

#define PI 3.14159265

using namespace std;

// unsigned char fader_list[9] = {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8};
class XTouch
{    
public:
    XTouch();
    ~XTouch();

    // TODO: add
    int    update(void);   // read + disperse data once
    void   save_current_parameters(void);
    void   load_saved_parameters(void);        // load parameters
    void   load_default_parameters(void);      // load default parameters
    // void   update_display(void);  update big LCD as menu if needed

    void   wave_demo();
    void   reset_faders();
    
    friend class Fader; // fader can write val and LCD
    // TODO: add objects in list
    Fader fader0 = Fader(0xE0);
    Fader fader1 = Fader(0xE1);
    Fader fader2 = Fader(0xE2);
    Fader fader3 = Fader(0xE3);
    Fader fader4 = Fader(0xE4);
    Fader fader5 = Fader(0xE5);
    Fader fader6 = Fader(0xE6);
    Fader fader7 = Fader(0xE7);
    Fader fader8 = Fader(0xE8);  // main channel, without LCD

private:

    /* 
    LCM message = 
    LCM host = 
    */

    // set up MIDI communication
    snd_rawmidi_t* midiin = nullptr;
    snd_rawmidi_t* midiout = nullptr;
    const char* portname = nullptr; // immutable ptr to mutable string
    int mode = SND_RAWMIDI_SYNC;

    char*  get_Xtouch_port(void);
    int    get_Xtouch_device_number (int card);
    void   error(const char *format, ...);
};

#endif
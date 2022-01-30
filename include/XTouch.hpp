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

#include "Fader.hpp"
// #include <Rotator.hpp>
// #include <Button.hpp>

using namespace std;

class XTouch
{    
public:
    XTouch();
    ~XTouch();

    // TODO: add
    void   update(void);   // read + disperse data
    void   save_current_parameters(void);
    void   load_saved_parameters(void);        // load parameters
    void   load_default_parameters(void);      // load default parameters
    // void   update_display(void);  update big LCD as menu if needed

    void   wave_demo(snd_rawmidi_t* midiout);
    void   reset_faders(snd_rawmidi_t* midiout);

    Fader fader0(0xE0);
    Fader fader1(0xE1);
    Fader fader2(0xE2);
    Fader fader3(0xE3);
    Fader fader4(0xE4);
    Fader fader5(0xE5);
    Fader fader6(0xE6);
    Fader fader7(0xE7);
    Fader fader8(0xE8);

private:

    /* 
    LCM message = 
    LCM host = 
    */

    // set up MIDI communication
    snd_rawmidi_t* midiin = nullptr;
    snd_rawmidi_t* midiout = nullptr;
    const char* portname = nullptr; // immutable ptr to mutable string

    char*  get_Xtouch_port(void);
    int    get_Xtouch_device_number (int card);
    void   error(const char *format, ...);
};

#endif
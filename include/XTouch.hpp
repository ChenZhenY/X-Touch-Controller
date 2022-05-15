/*!
 * @file XTouch.hpp
 * @brief define all the members and functionalities of XTouch controller.
 * read from XTouch using alsa MIDI under Mackie Control. Send data to RS.
 * display result on LCD display.
 */

#ifndef XTOUCH
#define XTOUCH

#include <fstream>
#include <iostream>
#include <vector>

#include <alsa/asoundlib.h>
#include <math.h>
#include <time.h>

#include "Fader.hpp"
// #include <Rotator.hpp>
// #include <Button.hpp>

#include "lcm/lcm-cpp.hpp"
#include "XTouch_Parameter.hpp"
#include "humanoid_menu_data_lcmt.hpp"

#define PI 3.14159265

using namespace std;

// unsigned char fader_list[9] = {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8};
class XTouch
{    
public:
    XTouch();
    ~XTouch();

    friend class Fader; // fader can write val and LCD
    vector<Fader> fader;

    // TODO: add helper functions
    void   save_current_parameters(void);
    void   load_saved_parameters(void);        // load parameters
    void   load_default_parameters(void);      // load default parameters

    int    update(void);   // main update loop
    void   midiin_handler(const unsigned char* buffer);   // handle input midi msg, send to different channel
    void   update_display(void);   // update fader LCD, add big LCD if needed
    void   update_fader_pos(void); // update fader position
    void   publish_to_lcm(void);   // send lcm msg
    // void   update_main_LCD()

    void   wave_demo(const unsigned char* buffer); // TODO: new thread for button control
    
    void   init_faders(vector<string>* key_obj);
    void   reset_faders();     // reset faders to 0 position
    void   reset_faders_mid(); // reset faders to midlle position


private:

    lcm::LCM lcm;
    XTouchMsg::XTouch_Parameter data_sent;        // for test
    XTouchMsg::humanoid_menu_data_lcmt menu_data; // for RS menu data

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
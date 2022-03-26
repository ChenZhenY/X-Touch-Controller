/*!
 * @file fader.hpp
 * @brief fader class:
 * fader read and process MIDI value, calculate the corresponding parameter value.
 * fader can be used to control different control parameters
 */


#ifndef FADER
#define FADER

#include <alsa/asoundlib.h>
#include "ControlParameters.hpp"

class Fader
{
public:
    ControlParameters* param;
    
    Fader(unsigned char channel);
    ~Fader();
    void command_handler(const unsigned char* buffer); // process MIDI input
    void set_val_now(const unsigned char* buffer);     // set fader value from MIDI input
    void set_val_now(int input);                       // TODO: process input LCM msg
    void save_val_now(void) {this->val_last_save = this->val_now;}  // save current value
    unsigned short int get_val_now(void){return val_now;}
    double get_val_param_now(void);                    // convert raw value to paramter value 
    double get_val_param_save(void);
    unsigned char get_channel(void) {return this->channel;}
    // void set_channel(unsigned char channel) {this->channel = channel;}
    unsigned char* set_LCD_msg(void); // return LCD MIDI msg

private:
    // only save raw data
    unsigned short int val_now;       // lastest raw value from MIDI 0-16384
    unsigned short int val_last_save; // raw value that last time saved
    const unsigned char channel;      // the first byte of msg, 0xE0-E8, can't be changed
};

#endif
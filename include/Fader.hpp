/*!
 * @file fader.hpp
 * @brief fader class:
 * fader read and process MIDI value, calculate the corresponding parameter value.
 * fader can be used to control different control parameters
 */

// TODO: add display_function in private and call it when new value are set

#include "ControlParameters.hpp"

#ifndef FADER
#define FADER

class Fader
{
public:
    ControlParameters* param;
    
    Fader(unsigned char channel);
    ~Fader();
    void set_val_now(const unsigned char* buffer) {this->val_now = (buffer[2]<<7) + buffer[1];} // process input MIDI
    void save_val_now(void) {this->val_last_save = this->val_now;}  // save current value
    double get_val_param_now(void);
    double get_val_param_save(void);
    unsigned char get_channel(void) {return this->channel;}

private:
    // only save raw data
    unsigned short int val_now;       // lastest raw value from MIDI 0-16384
    unsigned short int val_last_save; // raw value that last time saved
    const unsigned char channel;      // the first byte of msg, 0xE0-E8, unchange
};

Fader::Fader(unsigned char channel): channel(channel)
{
    // 9 faders total, which should have different channel strip
    this->val_now = 0;
    this->val_last_save = 0;
    this->val_param = 0;
    this->param = nullptr;
    this->channel = 0;
}

Fader::~Fader()
{
    this->param = nullptr;
}

double Fader::get_val_param_now(void) {
    double diff = double(this->param->get_ub() - this->param->get_lb());
    return double((this->val_now/16384)*diff) + double(this->param->get_lb());
}

double Fader::get_val_param_save(void) {
    double diff = double(this->param->get_ub() - this->param->get_lb());
    return double((this->val_last_save/16384)*diff) + double(this->param->get_lb());
}

#endif
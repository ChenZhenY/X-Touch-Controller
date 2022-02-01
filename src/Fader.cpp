#include "Fader.hpp"

void error(const char *format, ...);

Fader::Fader(unsigned char channel): channel(channel)
{
    // 9 faders total, which should have different channel strip
    this->val_now = 0;
    this->val_last_save = 0;
    this->param = nullptr;
}

Fader::~Fader()
{
    this->param = nullptr;
}

void Fader::set_val_now(const unsigned char* buffer) {

    if (buffer[0] == this->channel) {
        // set the val
        this->val_now = (buffer[2]<<7) + buffer[1];
    }
}

double Fader::get_val_param_now(void) {
    double diff = double(this->param->get_ub() - this->param->get_lb());
    return double((this->val_now/16384)*diff) + double(this->param->get_lb());
}

double Fader::get_val_param_save(void) {
    double diff = double(this->param->get_ub() - this->param->get_lb());
    return double((this->val_last_save/16384)*diff) + double(this->param->get_lb());
}

char* Fader::set_LCD_msg(void) {
    // static unsigned char lcd [15] = {0xf0, 0x00, 0x00, 0x66, 0x14, 0x12, 0x38, 0x4c, 0x52, 0x4c, 0x52, 0x35, 0x30, 0x20, 0xf7};
    static unsigned char msg [30];
    unsigned char header_up[7]   = {0xf0, 0x00, 0x00, 0x66, 0x14, 0x12, 0x00};
    unsigned char header_down[7] = {0xf0, 0x00, 0x00, 0x66, 0x14, 0x12, 0x38};
    unsigned char content_up[8]  = {0,0,0,0,0,0,0,0};
    unsigned char content_down[8]= {0,0,0,0,0,0,0,0};
    header_up[6] = (this->channel-0xe0)*7;
    header_down[6] = (this->channel-0xe0)*7 + 0x38;
    
    // msg sent follows ascii
    const char* name = this->param->get_name().c_str();
    strcat(content_up, name);
    // TODO: add number conversion strcat(content_down) change to memcpy
    content_up[7] = 0xf7;  // msg end bit
    content_down[7] = 0xf7;

    strcat(msg, header_up);
    strcat(msg, content_up);
    strcat(msg, header_down);
    strcat(msg, content_down); 
    return msg;
}
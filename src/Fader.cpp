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

void Fader::command_handler(const unsigned char* buffer) {
    // set val if updated
    this->set_val_now(buffer);

    int channel_index = this->get_channel() - 0xE0; // get the channel index
    // handle button operation (only 8 channels)
    // "rec": save current val, [90],[00-07],[7F/00] header,channel,up/down
    if ((buffer[0]==0x90) && (buffer[1]==channel_index) && (buffer[2]==0x7F)) {
        this->save_val_now();
        printf("%s channel value is saved: %f\n", param->get_name().c_str(), get_val_param_save());
    }
    // "solo": set current val to rec val: [90],[08-0F],[7F/00]
    if ((buffer[0]==0x90) && (buffer[1]==channel_index+0x08) && (buffer[2]==0x7F)) {
        this->val_now = this->val_last_save;
        printf("%s channel value is set to: %f \n", param->get_name().c_str(), get_val_param_now());
    }
}

void Fader::set_val_now(const unsigned char* buffer) {

    if (buffer[0] == this->channel) {
        // set the original val
        this->val_now = (buffer[2]<<7) + buffer[1];
    }
}

double Fader::get_val_param_now(void) {
    double diff = double(this->param->get_ub() - this->param->get_lb());
    return double((this->val_now/16384.0)*diff) + double(this->param->get_lb());
}

double Fader::get_val_param_save(void) {
    double diff = double(this->param->get_ub() - this->param->get_lb());
    return double((this->val_last_save/16384.0)*diff) + double(this->param->get_lb());
}

unsigned char* Fader::set_LCD_msg(void) {
    // static unsigned char lcd [15] = {0xf0, 0x00, 0x00, 0x66, 0x14, 0x12, 0x38, 0x4c, 0x52, 0x4c, 0x52, 0x35, 0x30, 0x20, 0xf7};
    static unsigned char msg [40];
    unsigned char header_up[7]   = {0xf0, 0x00, 0x00, 0x66, 0x14, 0x12, 0x00};
    unsigned char header_down[7] = {0xf0, 0x00, 0x00, 0x66, 0x14, 0x12, 0x38};
    unsigned char content_up[8]  = {0,0,0,0,0,0,0,0};
    unsigned char content_down[8]= {0,0,0,0,0,0,0,0};
    // char header_up[7]   = {0xf0, 0x00, 0x00, 0x66, 0x14, 0x12, 0x00};
    // char header_down[7] = {0xf0, 0x00, 0x00, 0x66, 0x14, 0x12, 0x38};
    header_up[6] = (this->channel-0xe0)*7;          // select the channel
    header_down[6] = (this->channel-0xe0)*7 + 0x38;
    
    // msg sent follows ascii
    const char* name = this->param->get_name().c_str();
    double value = this->get_val_param_now();
    
    // add number and control value to the content
    // char content_up[8]  = {0,0,0,0,0,0,0,0};
    // char content_down[8]= {0,0,0,0,0,0,0,0};
    strcpy((char*)content_up, name); // control param name
    sprintf((char*)content_down, "%5.2f", value);  // control param value
    content_up[7] = 0xf7;     // msg end bit
    content_down[7] = 0xf7;

    memcpy(msg, header_up, sizeof header_up);
    memcpy(msg+7, content_up, sizeof content_up);
    memcpy(msg+15, header_down, sizeof header_down);
    memcpy(msg+22, content_down, sizeof content_down);
    // memcpy(msg, header_up, 0, sizeof );
    // strcat((char*) msg, (char*)header_up);
    // strcat((char*) msg, (char*)content_up);
    // strcat((char*) msg, (char*)header_down);
    // strcat((char*) msg, (char*)content_down);

    // strcat(msg, header_up);
    // strcat(msg, content_up);
    // strcat(msg, header_down);
    // strcat(msg, content_down);
    return msg;
}
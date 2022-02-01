#include "XTouch.hpp"


XTouch::XTouch() {
    // setting up the MIDI connection
    int status;
    this->portname = get_Xtouch_port();
    if ((status = snd_rawmidi_open(&midiin, &midiout, portname, this->mode)) < 0) {
      error("Problem opening MIDI input: %s", snd_strerror(status));
      exit(1);
    }
    reset_faders(this->midiout);

    // set up faders and parameters mapping

    // TODO:set up LCM msg and host
}

XTouch::~XTouch() {
    snd_rawmidi_close(this->midiin);
    midiin  = nullptr;    // snd_rawmidi_close() does not clear invalid pointer,
    midiout = nullptr;    // so might be a good idea to erase it after closing.
}

int XTouch::update(void) {
   // read: receive msg and send it to all the components (e.g fader)
   int status = -1;
   unsigned char buffer [3];
   status = snd_rawmidi_read(midiin, buffer, 3);

   if ((status < 0) && (status != -EBUSY) && (status != -EAGAIN)) {
      error("Problem reading MIDI input: %s",snd_strerror(status));
      return status;
   } else if (status >= 0) {
      // print and hold the fader position
      printf("raw msg: 0x%x %x %x\n", buffer[0], buffer[1], buffer[2]);
      if ((status = snd_rawmidi_write(this->midiout, buffer, 3)) < 0) {
         error("Problem writing to MIDI output: %s", snd_strerror(status));
      }
      // send msg to all components
      this->fader0.set_val_now(buffer);
      this->fader1.set_val_now(buffer);
      this->fader2.set_val_now(buffer);
      this->fader3.set_val_now(buffer);
      this->fader4.set_val_now(buffer);
      this->fader5.set_val_now(buffer);
      this->fader6.set_val_now(buffer);
      this->fader7.set_val_now(buffer);
      this->fader8.set_val_now(buffer);

      // write display
      unsigned char* msg = this->fader3.set_LCD_msg();
      status = snd_rawmidi_write(midiout, msg, 15);
      if (status<0){
         error("Problem writing to MIDI output: %s", snd_strerror(status));
      }
   }
   return status;
}

void XTouch::wave_demo(snd_rawmidi_t* midiout) {
    
    unsigned char fader[9][3] = {{0xE0, 60, 0},{0xE1, 60, 0},{0xE2, 60, 0},
         {0xE3, 60, 0},{0xE4, 60, 0},{0xE5, 60, 0},{0xE6, 60, 0},{0xE7, 60, 0},{0xE8, 60, 0}};
    
    int status = -1;
    int ctrl = 0;
    int lsb = 0;
    int msb = 0;
    float w = 0.0006f;
    float k = 2*PI/9;
    float t = 0;
    float wait = 1;

    while (1)
    {
        for (int i=0; i<9; i++) {
            ctrl = (int)(8192 + 8191*sin(k*i-w*t));
            // ctrl = t;
            msb = (ctrl&16256)>>7; // (ctrl&(127<<7))>>7;
            lsb = (ctrl&127); 

            fader[i][2] = msb;
            fader[i][1] = lsb;
            status = snd_rawmidi_write(midiout, fader[i], 3);
            if (status<0){
                error("Problem writing to MIDI output: %s", snd_strerror(status));
                exit(1);
            }
        }
        t+=wait;
    }
    
}

// get the device name for X-Touch

char* XTouch::get_Xtouch_port(void){
   int status;
   int card = -1;  // use -1 to prime the pump of iterating through card list
   int device = -1;
   static char port[32];
   memset(port, 0, 32);

   if ((status = snd_card_next(&card)) < 0) {
      error("cannot determine card number: %s", snd_strerror(status));
      exit(1);
   }
   if (card < 0) {
      error("no sound cards found");
      exit(1);
   }

   while (card >= 0) {
      device = get_Xtouch_device_number(card);
      if (device>=0){
         sprintf(port, "hw:%d,%d,0", card, device);
         return port;
      }
      if ((status = snd_card_next(&card)) < 0) {
         error("cannot determine card number: %s", snd_strerror(status));
         break;
      }
   }
   sprintf(port, "get port failed");
   return port;
}
// list_midi_devices_on_card -- For a particular "card" look at all
//   of the "devices/subdevices" on it and print information about it
//   if it can handle MIDI input and/or output.
//

int XTouch::get_Xtouch_device_number(int card) {
   
   snd_ctl_t *ctl;
   snd_rawmidi_info_t *info;
   const char *dev_name;
   const char *target_dev = "X-Touch";
   
   char name[32];
   memset(name, '\0', 32);
   int device = -1;
   int status;
   // int subs_in, subs_out;

   sprintf(name, "hw:%d", card);
   if ((status = snd_ctl_open(&ctl, name, 0)) < 0) {
      error("cannot open control for card %d: %s", card, snd_strerror(status));
      return -1;
   }
   do {
      status = snd_ctl_rawmidi_next_device(ctl, &device);
      if (status < 0) {
         error("cannot determine device number: %s", snd_strerror(status));
         break;
      }
      if (device >= 0) {
         snd_rawmidi_info_alloca(&info);
         snd_rawmidi_info_set_device(info, device);

         snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_INPUT);
         snd_ctl_rawmidi_info(ctl, info);
         // subs_in = snd_rawmidi_info_get_subdevices_count(info);
         snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_OUTPUT);
         snd_ctl_rawmidi_info(ctl, info);
         // subs_out = snd_rawmidi_info_get_subdevices_count(info);

         dev_name = snd_rawmidi_info_get_name(info);
         if (strcmp(dev_name, target_dev) == 0)
            return device;
      }
   } while (device >= 0);
   snd_ctl_close(ctl);
   return -1;
}

void XTouch::reset_faders(snd_rawmidi_t* midiout) {
   
   unsigned char zero[3] = {0xE0, 60, 0};
   int status = -1;
   for (int i=0; i<9; i++){
      status = snd_rawmidi_write(midiout, zero, 3);
      zero[0] += 1;
      if (status<0){
         error("Problem writing to MIDI output: %s", snd_strerror(status));
         exit(1);
      }
   }
}

// error -- print error message
void XTouch::error(const char *format, ...) {
   va_list ap;
   va_start(ap, format);
   vfprintf(stderr, format, ap);
   va_end(ap);
   putc('\n', stderr);
}
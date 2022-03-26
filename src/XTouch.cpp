#include "XTouch.hpp"


XTouch::XTouch() {
    // setting up the MIDI connection
    int status;
    this->portname = get_Xtouch_port();
    if ((status = snd_rawmidi_open(&midiin, &midiout, portname, this->mode)) < 0) {
      error("Problem opening MIDI input: %s", snd_strerror(status));
      exit(1);
    }

   // initialize fader list
   for (int i=0; i<9; i++) {
      fader.push_back(Fader(0xE0+i));
   }

   reset_faders();
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
   // printf("raw msg: 0x%x %x %x\n", buffer[0], buffer[1], buffer[2]);
   // handle reading fail
   if ((status < 0) && (status != -EBUSY) && (status != -EAGAIN)) {
      error("Problem reading MIDI input: %s",snd_strerror(status));
      return status;
   }

   // send new msg to all faders and update values to display
   unsigned char* msg;
   unsigned char set_val [3];
   for (int i = 0; i<9; i++) {
      fader[i].command_handler(buffer);

      // display value and name on LCD
      if (fader[i].get_channel()<=0xe7) {      // we only have 8 LCD
         msg = fader[i].set_LCD_msg();
         status = snd_rawmidi_write(midiout, msg, 40);
      }
      if (status<0){
         error("Problem writing to MIDI output: %s", snd_strerror(status));
      }

      // set fader position
      unsigned short int val_now = fader[i].get_val_now();
      set_val[0] = fader[i].get_channel();
      set_val[1] = (unsigned char)fader[i].get_val_now() & 127;
      set_val[2] = fader[i].get_val_now() >> 7;
      // printf("buffer %x my %x \n", buffer[1], set_val[1]);
      if ((status = snd_rawmidi_write(this->midiout, set_val, 3)) < 0) {
         error("Problem writing to MIDI output: %s", snd_strerror(status));
      }
   }


   // send LCM msg
   if (!lcm.good()) {
      printf("lcm fail to set up");
   }
   else {
      for (int i=0; i<8; i++) {
         data_sent.channel_name[i] = fader[i].param->get_name();
         // printf("name  %s", fader[i].param->get_name().c_str());
         data_sent.channel_value[i]= fader[i].get_val_param_now();
      }
      lcm.publish("XTouch", &data_sent);
   }
   return status;
}

void XTouch::wave_demo(const unsigned char* buffer) {
   
   // static bool demo = false;

   // if ((buffer[0]==0x90)&&(buffer[1]==0x54)){
   //    demo = !demo;
   // }

   // if (demo)
   // {

   // }
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

void XTouch::reset_faders() {
   
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
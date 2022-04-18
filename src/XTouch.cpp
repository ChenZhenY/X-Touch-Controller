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
   // set fader to midlle places
   reset_faders_mid();
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

   midiin_handler(buffer);
   update_display();
   update_fader_pos();
   publish_to_lcm();

   return status;
}

void XTouch::midiin_handler(const unsigned char* buffer) {
   // handle input midi msg, send to different channel

   // 9 faders update
   for (int i = 0; i<9; i++) {
      fader[i].command_handler(buffer);
   }

   // MARKER to record the json parameters
   time_t raw_time;
   time(&raw_time);
   string folder = "../json_saved";
   string header = "/params ";
   string suffix = ".json";
   string filename =  folder + header + ctime(&raw_time) + suffix;
   if ((buffer[0]==0x90) && (buffer[1]==0x54) && (buffer[2] == 0x7F)) {
      ofstream o(filename);
      o<<menu_obj<<endl;
   }

   // TODO: update buttons and encoders
}

void XTouch::update_display(void) {

   // update fader LCD
   int status = -1;
   unsigned char* msg;
   for (int i=0; i<8; i++) {
      // display value and name on 8 fader LCD
      msg = fader[i].set_LCD_msg();
      status = snd_rawmidi_write(midiout, msg, 40);
      if (status<0){
         error("Problem writing to MIDI output: %s", snd_strerror(status));
      }
   }

   // TODO: add big LCD if needed
}

void XTouch::update_fader_pos(void) {
   // update fader position

   int status = -1;
   unsigned char set_val [3];
   for (int i=0; i<9; i++) {
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

void XTouch::publish_to_lcm() {
   // send LCM msg
   if (!lcm.good()) {
      printf("lcm fail to set up");
   }
   else {
      // TODO: find better way to capsule msg, add button etc.
      // for (int i=0; i<8; i++) {
      //    // data_sent.channel_name[i] = fader[i].param->get_name();
      //    // printf("name  %s", fader[i].param->get_name().c_str());
      //    // data_sent.channel_value[i]= fader[i].get_val_param_now();
      // }
      menu_data.Kd_body[0] = menu_obj["Kd_body"]["x"];
      menu_data.Kd_body[1] = menu_obj["Kd_body"]["y"];
      menu_data.Kd_body[2] = menu_obj["Kd_body"]["z"];

      menu_data.Kd_cam[0] = menu_obj["Kd_cam"]["x"];
      menu_data.Kd_cam[1] = menu_obj["Kd_cam"]["y"];
      menu_data.Kd_cam[2] = menu_obj["Kd_cam"]["z"];

      menu_data.Kd_clm[0] = menu_obj["Kd_clm"]["x"];
      menu_data.Kd_clm[1] = menu_obj["Kd_clm"]["y"];
      menu_data.Kd_clm[2] = menu_obj["Kd_clm"]["z"];

      menu_data.Kd_foot[0] = menu_obj["Kd_foot"]["x"];
      menu_data.Kd_foot[1] = menu_obj["Kd_foot"]["y"];
      menu_data.Kd_foot[2] = menu_obj["Kd_foot"]["z"];

      menu_data.Kd_joint[0] = menu_obj["Kd_joint"]["x"];
      menu_data.Kd_joint[1] = menu_obj["Kd_joint"]["y"];
      menu_data.Kd_joint[2] = menu_obj["Kd_joint"]["z"];

      menu_data.Kd_ori[0] = menu_obj["Kd_ori"]["x"];
      menu_data.Kd_ori[1] = menu_obj["Kd_ori"]["y"];
      menu_data.Kd_ori[2] = menu_obj["Kd_ori"]["z"];

      menu_data.Kp_body[0] = menu_obj["Kp_body"]["x"];
      menu_data.Kp_body[1] = menu_obj["Kp_body"]["y"];
      menu_data.Kp_body[2] = menu_obj["Kp_body"]["z"];

      menu_data.Kp_cam[0] = menu_obj["Kp_cam"]["x"];
      menu_data.Kp_cam[1] = menu_obj["Kp_cam"]["y"];
      menu_data.Kp_cam[2] = menu_obj["Kp_cam"]["z"];

      menu_data.Kp_clm[0] = menu_obj["Kp_clm"]["x"];
      menu_data.Kp_clm[1] = menu_obj["Kp_clm"]["y"];
      menu_data.Kp_clm[2] = menu_obj["Kp_clm"]["z"];

      menu_data.Kp_foot[0] = menu_obj["Kp_foot"]["x"];
      menu_data.Kp_foot[1] = menu_obj["Kp_foot"]["y"];
      menu_data.Kp_foot[2] = menu_obj["Kp_foot"]["z"];

      menu_data.Kp_joint[0] = menu_obj["Kp_joint"]["x"];
      menu_data.Kp_joint[1] = menu_obj["Kp_joint"]["y"];
      menu_data.Kp_joint[2] = menu_obj["Kp_joint"]["z"];

      menu_data.Kp_ori[0] = menu_obj["Kp_ori"]["x"];
      menu_data.Kp_ori[1] = menu_obj["Kp_ori"]["y"];
      menu_data.Kp_ori[2] = menu_obj["Kp_ori"]["z"];
      
      lcm.publish("XTouch", &menu_data);
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

void XTouch::init_faders(vector<string>* key_obj) {
   // initialize fader value
   string name;
   for (int i=0; i<9; i++) {
      if (i<key_obj->size()){
         name = key_obj->at(i);
         fader[i].param_name = name;
         fader[i].param_xyz = "x";
         fader[i].init_val["x"]  = menu_obj[name]["x"];
         fader[i].init_val["y"]  = menu_obj[name]["y"];
         fader[i].init_val["z"]  = menu_obj[name]["z"];
      }
   }
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

void XTouch::reset_faders_mid() {
   
   unsigned char zero[3] = {0xE0, 0, 64};
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
/************************************
 * Programmer: Zhenyang (Daniel) Chen
 * Date: Mon Jan 24, 2022
 * 
 * Description: Read MIDI signal from X-Touch DAW using ALSA rawmidi 
 * interface and send to LCM channel.
 * 
 * Check: ALSA system installed in your PC can be found running: 
 * cat /proc/asound/version 
 * Which should return something like:
 * Advanced Linux Sound Architecture Driver Version 1.0.17.
 * Then check with X-TOUCH setting, turn on when holding channel 1 
 * select button. Setting channel 1 to MC and channel 2 to USB, press 
 * select to confirm. To check the communication between X-touch and 
 * your PC, run amidi -l to find the port and amidi -d -p [portnumber] 
 * to see the received data.
 * 
 * Compile: g++ [filename].cpp -o [exename] -lasound
 * 
 * Online documentation notes:
 * http://www.alsa-project.org/alsa-doc/alsa-lib/rawmidi.html
 * This file also refers to examples provided by Craig Stuart Sapp from Stanford
 * https://ccrma.stanford.edu/~craig/articles/linuxmidi/alsa-1.0/
*/

#include <alsa/asoundlib.h>     /* Interface to the ALSA system */

#include <math.h>

#define PI 3.14159265


// function declarations:
void   error(const char *format, ...);
char*  get_Xtouch_port(void);
int    get_Xtouch_device_number (int card);
void   reset_faders(snd_rawmidi_t* midiout);
void   wave_demo(snd_rawmidi_t* midiout);

///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
   int status;
   int count = 0;
   int mode = SND_RAWMIDI_SYNC;
   snd_rawmidi_t* midiin = NULL;
   snd_rawmidi_t* midiout = NULL;
   unsigned char buffer[3];        // Storage for input buffer received

   const char* portname = get_Xtouch_port();  // see alsarawportlist.c example program

   if ((status = snd_rawmidi_open(&midiin, &midiout, portname, mode)) < 0) {
      error("Problem opening MIDI input: %s", snd_strerror(status));
      exit(1);
   }
   
   reset_faders(midiout);
   wave_demo(midiout);

   snd_rawmidi_close(midiin);
   midiin  = NULL;    // snd_rawmidi_close() does not clear invalid pointer,
   midiout = NULL;    // so might be a good idea to erase it after closing.
   return 0;
}

// get the device name for X-Touch

char* get_Xtouch_port(void){
   int status;
   int card = -1;  // use -1 to prime the pump of iterating through card list
   int device = -1;
   static char port[32];
   memset(port, 0, 32);

   if ((status = snd_card_next(&card)) < 0) {
      error("cannot determine card number: %s", snd_strerror(status));
      return " ";
   }
   if (card < 0) {
      error("no sound cards found");
      return " ";
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
   return "noXtouch";
}

// list_midi_devices_on_card -- For a particular "card" look at all
//   of the "devices/subdevices" on it and print information about it
//   if it can handle MIDI input and/or output.
//

int get_Xtouch_device_number(int card) {
   
   snd_ctl_t *ctl;
   snd_rawmidi_info_t *info;
   const char *dev_name;
   const char *target_dev = "X-Touch";
   
   char name[32];
   memset(name, '\0', 32);
   int device = -1;
   int status;
   int subs, subs_in, subs_out;
   int sub, in, out;

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
         subs_in = snd_rawmidi_info_get_subdevices_count(info);
         snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_OUTPUT);
         snd_ctl_rawmidi_info(ctl, info);
         subs_out = snd_rawmidi_info_get_subdevices_count(info);
         subs = subs_in > subs_out ? subs_in : subs_out;

         dev_name = snd_rawmidi_info_get_name(info);
         if (strcmp(dev_name, target_dev) == 0)
            return device;
      }
   } while (device >= 0);
   snd_ctl_close(ctl);
   return -1;
}

void reset_faders(snd_rawmidi_t* midiout) {
   
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
   sleep(0.3);
}

void wave_demo(snd_rawmidi_t* midiout) {
    
    unsigned char fader[9][3] = {{0xE0, 60, 0},{0xE1, 60, 0},{0xE2, 60, 0},
         {0xE3, 60, 0},{0xE4, 60, 0},{0xE5, 60, 0},{0xE6, 60, 0},{0xE7, 60, 0},{0xE8, 60, 0}};
    
    int status = -1;
    float w = 0.1f;
    float k = 2*PI/9;
    float t = 0;
    float wait = 0.4;

    while (1)
    {
        for (int i=0; i<9; i++) {
            fader[i][2] = (int)(8101 + 8100*sin(k*i-w*t));
            status = snd_rawmidi_write(midiout, fader[i], 3);
            if (status<0){
                error("Problem writing to MIDI output: %s", snd_strerror(status));
                exit(1);
            }
        }
        t+=wait;
        sleep(wait);
    }
    
}

// error -- print error message

void error(const char *format, ...) {
   va_list ap;
   va_start(ap, format);
   vfprintf(stderr, format, ap);
   va_end(ap);
   putc('\n', stderr);
}

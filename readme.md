# X-TOUCH-CONTROLLER
Zhenyang Chen
## Intro:
Tuning your robot parameters like a musician!

## TODO:
- [x] Add LCM communication for sending parameters
- [ ] Add buttons to store recent parameters/ load parameters
- [ ] Add scientific representation to the program
- [ ] Read parameters from txt or other program, without changing program. (also need to confirm this with Robosoftware)

## Usage:
1. clean the build directory and build the program ```cd ./build & cmake .. & make```. Excutable is ```./XTOUCH```
2. The program first need to know what parameters you want to tune and their ranges, and then map them to corresponding sliders channels (will support button later). So you need to specify the parameters and their mapping in ```main.cpp```.

## Troubleshooting:
1. XTouch connection. We can build the MIDI connection between xtouch and PC with USB cable. And no extra drivers are required (ubuntu 18.04). You can check the connection and input signal by running these in terminal  ```amidi -l/ --dump -p *port``` or ```aseqdump -l/ -p *port``` to make sure you can read the raw data.
2. Debug: if you are using vscode, the tasks.json and launch.json have been configured, and you can debug the code by hitting F5.

## Reference:
[Mackie Control](https://github.com/Silhm/bcf-scribble-strips/wiki/Understanding-Mackie-Control-Protocol)

[MIDI on linux (ALSA and Jack) Overview](http://www.tedfelix.com/linux/linux-midi.html#low-latency-kernel)

[Stanford MIDI code example](https://ccrma.stanford.edu/~craig/articles/linuxmidi/alsa-1.0/)

[ALSA reference](https://www.alsa-project.org/alsa-doc/alsa-lib/index.html)

[Linux midi guide](https://tldp.org/HOWTO/MIDI-HOWTO.html#toc7)

[MIDI msg definition](https://sites.uci.edu/camp2014/2014/04/30/managing-midi-pitchbend-messages/#:~:text=The%20MIDI%20protocol%20specifies%20that,16%2C383%20means%20maximum%20upward%20bend.)
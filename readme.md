# X-TOUCH-CONTROLLER
Zhenyang Chen
## Intro:
Tuning your robot parameters like a musician!

## TODO:
- [x] Add LCM communication for sending parameters
- [x] Add buttons to store recent parameters/ load parameters
- [x] Read parameters from json (RS), load all the faders value.
- [ ] add encoder to choose which parameters to display on faders (in midihandler function and make sure each fader corresponds to one param name/value)
- [x] save json setting with button
- [ ] consider adding "range" param in the json file (is hardcoded in ```main.cpp```currently)
- [ ] Add scientific representation to the program

## Integration to RS:
Read and set initial position from json. Publish updated value from slider to menu data (humanoid)
1. msg type: need to be consistent with [robot]_menu_data_lcmt.lcm
2. initial json setting: simulator/unity_Visualization/Assets/default_config_[robot].json
3. send new update value
   
## Usage:
1. clean the build directory and build the program ```cd ./build & cmake .. & make```. Excutable is ```./XTOUCH```
2. (will be updated): The program first need to know what parameters you want to tune and their ranges, and then map them to corresponding sliders channels (will support button later). So you need to specify the parameters and their mapping in ```main.cpp```.
3. New parameters in lcm msg: the program can fetch the new parameters automatically (obj, num and bool). But if you want to send them, you need to add them in LCM msg which is encapsuled in publish_to_lcm() in XTouch class.

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
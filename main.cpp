/*
 * @file main.cpp
 * @brief: setting up the functions in new framework. Parameters should be independent
 * to XTouch class.
 */

#include "XTouch.hpp"
#include <fstream>
#include <json.hpp>

using json = nlohmann::json;

json menu_obj;  // all the object (assume all contain x, y, z values)
json menu_obj_init; // initial obj values
json menu_bool; // all the boolean values, using buttons
json menu_num;  // all single number values

// keep track of the key name of parameters
vector<string> key_obj;
vector<string> key_bool;
vector<string> key_num;

void setup_data_from_json(json menu_init);

int main(int argc, char *argv[]) {

    std::ifstream in("../default_config_humanoid.json");
    json menu_init = json::parse(in);
    setup_data_from_json(menu_init);

    XTouch Xcontroller;
    Xcontroller.init_faders(&key_obj);
    Xcontroller.update_display();

    int status = 1;
    while (status) {
        status = Xcontroller.update();
    }
    return 0;
}

void setup_data_from_json(json menu_init) {
    // set different type of parameters (bool, obj, num) to different jsons
    json temp;
    for(json::iterator it= menu_init.begin(); it!=menu_init.end(); ++it){
        if (it.value().is_object()) {
            temp = it.value();
            temp["range"] = 10.0;        // TODO: setup half range value in original json??
            menu_obj[it.key()] = temp;
            menu_obj_init[it.key()] = temp;
            key_obj.push_back(it.key());
        }
        if (it.value().is_number()) {
            menu_num[it.key()] = it.value();
            key_num.push_back(it.key());
        }
        if (it.value().is_boolean()) {
            menu_bool[it.key()] = it.value();
            key_bool.push_back(it.key());
        }
    }
}
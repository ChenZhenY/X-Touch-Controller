// define the control parameters used in robotsoftware
#ifndef CONTROLPARAMETERS
#define CONTROLPARAMETERS

#include <string>
#include <iostream>

using namespace std;

// TODO: add generic type to this class
class ControlParameters
{
public:
    ControlParameters(string s, double lb, double ub);
    // ControlParameters(Fader* input) {this->channel = input;}
    // ~ControlParameters() {this->channel = nullptr;}
    double get_ub(void) {return this->upper_bound;}
    double get_lb(void) {return this->lower_bound;}
    void set_ub(double ub) {this->upper_bound = ub;}
    void set_lb(double lb) {this->lower_bound = lb;}
    string get_name(void)  {return this->name;}

private:
    string name;
    double lower_bound;
    double upper_bound;
};



#endif
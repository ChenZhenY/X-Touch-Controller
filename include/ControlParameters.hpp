// define the control parameters used in robotsoftware

#ifndef CONTROLPARAMETERS
#define CONTROLPARAMETERS

#include <string>
#include <iostream>

template <typename T>
class ControlParameters
{
public:
    ControlParameters(string s, T lb, T ub);
    // ControlParameters(Fader* input) {this->channel = input;}
    // ~ControlParameters() {this->channel = nullptr;}
    T get_ub(void) {return this->upper_bound;}
    T get_lb(void) {return this->lower_bound:}
    void set_ub(T ub) {this->upper_bound = ub;}
    void set_lb(T lb) {this->lower_bound = lb;}

private:
    string name;
    T lower_bound;
    T upper_bound;
};

ControlParameters::ControlParameters(string s, T lb, T ub):name(s)
{
    if (lb>ub) {
        std::cout<<"Make sure upper bound > lower bound"<<std::endl;
        exit(1);
    }
    this->lower_bound = lb;
    this->upper_bound = ub;
}

#endif
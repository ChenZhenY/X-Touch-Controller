#include "ControlParameters.hpp"

ControlParameters::ControlParameters(string s, double lb, double ub):name(s)
{
    if (lb>ub) {
        std::cout<<"Make sure upper bound > lower bound"<<std::endl;
        exit(1);
    }
    this->lower_bound = lb;
    this->upper_bound = ub;
}
//
// Created by YamEl on 12/15/2021.
//

#include "Road.h"
void remove_after_dots(string &str) {
    str.erase(str.find_last_not_of('0') + 1, string::npos );
    if(str.find('.') == str.length()-1)
    {
        str.erase (str.find_last_not_of('.') + 1, string::npos );
    }
}

//Constructor
Road::Road(int fromJunction, int toJunction, double length, double c)
: fromJunction(fromJunction), toJunction(toJunction), length(length){
}

//Getters
int Road::getFromJunction() const {
    return fromJunction;
}
int Road::getToJunction() const {
    return toJunction;
}
double Road::getLength() const {
    return length;
}
double Road::getAirPollution() const {
    return airPollution;
}
double Road::getC() const {
    return c;
}

//Setters
void Road::setFromJunction(int fromJunction) {
    Road::fromJunction = fromJunction;
}
void Road::setToJunction(int toJunction) {
    Road::toJunction = toJunction;
}
void Road::setLength(double length) {
    Road::length = length;
}
void Road::setC(double c) {
    Road::c = c;
}
const Road& Road::operator++() {
    airPollution += (static_cast<double >(c) / length);
    return *this;
}

const Road& Road::operator++(int) {
    Road &temp = *this;
    airPollution += c / length;;
    return temp;
}

ostream& operator<<(ostream& out, const Road& road){
    out << double2STR(road.getLength());
    return out;
}


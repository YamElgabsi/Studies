//
// Created by Yam Elgabsi on 11/06/2022.
//
#include "SimObject.h"



const string &SimObject::getName() const {
    return this->name;
}

Point *SimObject::getLocation() {
    return &location;
}

void SimObject::setLocation(const Point &location) {
    this->location = location;
}

void SimObject::printLocation() { cout << location;};




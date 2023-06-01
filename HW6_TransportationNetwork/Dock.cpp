//
// Created by YamEl on 5/17/2022.
//

#include "Dock.h"
#include <utility>

int Dock::dock_counter = 0;

int Dock::getType() const {
    return type;
}


Dock::Dock(int type) : type(type), id(dock_counter++) {}

int Dock::getId() const {
    return id;
}

bool Dock::operator==(const Dock &rhs) const {
    return id == rhs.id;
}

bool Dock::operator!=(const Dock &rhs) const {
    return !(rhs == *this);
}



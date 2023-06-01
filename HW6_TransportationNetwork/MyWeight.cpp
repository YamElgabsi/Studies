//
// Created by YamEl on 5/20/2022.
//

#include "MyWeight.h"

bool MyWeight::weighted = true;

MyWeight::MyWeight(int time):time(time) {
}

MyWeight::MyWeight(const MyWeight &&other) {
    this->time = other.time;

}

void MyWeight::setTime(int time) {
    this->time = time;
}

void MyWeight::makeWeighted() {
    weighted= true;
}

void MyWeight::makeUnWeighted() {
    weighted = false;
}

bool MyWeight::isWeighted() const {
    return weighted;
}

int MyWeight::getWeight() const {
    if (!weighted) return 1;
    return time;
}

double MyWeight::getHour() const {
    return time/60;
}

bool MyWeight::operator==(const MyWeight &rhs) const {
    if (!weighted) return true;
    return time == rhs.time;
}

bool MyWeight::operator!=(const MyWeight &rhs) const {
    if (!weighted) return false;
    return time != rhs.time;
}

bool MyWeight::operator<(const MyWeight &rhs) const {
    if (!weighted) return false;
    return time < rhs.time;
}

bool MyWeight::operator>(const MyWeight &rhs) const {
    if (!weighted) return false;
    return rhs < *this;
}

bool MyWeight::operator<=(const MyWeight &rhs) const {
    if (!weighted) return true;
    return !(rhs < *this);
}

bool MyWeight::operator>=(const MyWeight &rhs) const {
    if (!weighted) return true;
    return !(*this < rhs);
}

ostream &operator<<(ostream &os, const MyWeight &weight) {
    os << weight.time;
    return os;
}



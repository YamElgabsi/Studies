//
// Created by YamEl on 12/15/2021.
//

#include "Car.h"

//Constructor
Car::Car(int id, int location)
: id(id), location(location){}

//Getters
 int Car::getId() const {
    return id;
}
 int Car::getLocation() const {
    return location;
}

//Setters
void Car::setId( int id) {
    Car::id = id;
}
void Car::setLocation( int location) {
    Car::location = location;
}

ostream &operator<<(ostream& out, const Car &car) {
    out << car.getId() +1;
    return out;
}

//
// Created by YamEl on 1/1/2022.
//

#include "Cars.h"

//Car
//Constructor
Car::Car(unsigned int id, unsigned int location, char type)
        : id(id), location(location){
    stringstream str;
    str << type << id;
    str >> name;
}

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

const string &Car::getName() const {
    return name;
}

//operators
bool operator<(const Car& lhs, const Car& rhs){
    return lhs.getName().compare(rhs.getName()) < 0;
}
bool operator==(const Car& lhs, const Car& rhs){
    return lhs.getName().compare(rhs.getName()) == 0;
}

ostream &operator<<(ostream& out, const Car &car) {
    out << car.getName();
    return out;
}

//FamilyCar:

unsigned int FamilyCar::getAirPollution() const {
    return 2;
}

string FamilyCar::toString() const {
    return Car::getName();
}

ostream &operator<<(ostream& out, FamilyCar& familyCar) {
    out << familyCar.toString();
    return out;
}
//luxuyCar
unsigned int LuxuryCar::getAirPollution() const {
    return 3;
}

string LuxuryCar::toString() const {
    return Car::getName();
}

ostream &operator<<(ostream& out, LuxuryCar& luxuryCar) {
    out << luxuryCar.toString();
    return out;
}

//sportsCar

unsigned int SportsCar::getAirPollution() const {
    return 4;
}

string SportsCar::toString() const {
    return Car::getName();
}

ostream &operator<<(ostream& out, SportsCar& sportsCar) {
    out << sportsCar.toString();
    return out;
}

//Masarati
unsigned int Maserati::getAirPollution() const {
    return SportsCar::getAirPollution();
}

string Maserati::toString() const {
    return getName();
}

ostream &operator<<(ostream& out, Maserati& maserati) {
    out << maserati.toString();
    return out;
}





//
// Created by YamEl on 12/15/2021.
//

#include "Junction.h"

//Constructor
Junction::Junction(int id) : id(id) {

}

//Getters
int Junction::getId() const {
    return id;
}


//Setters
void Junction::setId(int id) {
    Junction::id = id;
}

//Function
void Junction::insertCar(Car car){
    cars.insert(car);
}

void Junction::removeCar(int carId){
    cars.remove(carId);
}

ostream& operator<<(ostream& out, const Junction& junction){
    out << junction.id +1 << ": " << junction.cars;
    return out;

}
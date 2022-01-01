//
// Created by YamEl on 12/15/2021.
//

#ifndef HW03_CAR_H
#define HW03_CAR_H

#include "Car.h"
#include <iostream>

using namespace std;

class Car {
private:
     int id;
     int location; //junction_id
     //thous above not unsigned because the "NO_CAR" default is -1

public:
    //the Big Three does not have implementation because the default one is good enough(int)

    //Constructor
    Car(int id = -1, int location = -1);

    //Getters
    int getId() const;
    int getLocation() const;

    //Setters
    void setId(int id);
    void setLocation(int location);

    friend ostream& operator<<(ostream& out, const Car& car);
};

ostream& operator<<(ostream& out, const Car& car);

#endif //HW03_CAR_H

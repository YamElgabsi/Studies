//
// Created by YamEl on 12/15/2021.
//

#ifndef HW03_JUNCTION_H
#define HW03_JUNCTION_H

#include "Junction.h"
#include "Road.h"
#include "Car.h"
#include "CarLinkedList.h"
#include <iostream>
using namespace std;

class Junction {
private:
    int id;
    CarLinkedList cars;


public:
    //the Big Three does not have implementation because the default one is good enough(int)

    //Constructor
    Junction(int id = -1);

    //Getters
    int getId() const;

    //Setters
    void setId(int id);

    //Function
    void insertCar(Car car);
    void removeCar(int carId);

    friend ostream& operator<<(ostream& out, const Junction& junction);


};

ostream& operator<<(ostream& out, const Junction& junction);


#endif //HW03_JUNCTION_H

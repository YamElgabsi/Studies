//
// Created by YamEl on 12/15/2021.
//

#ifndef HW03_JUNCTION_H
#define HW03_JUNCTION_H

#include "Junction.h"
#include "Road.h"
#include "Car.h"
#include "LinkedList.h"
#include <iostream>
using namespace std;

class Junction {
private:
    unsigned int id;


public:
    //the Big Three does not have implementation because the default one is good enough(int)

    //Constructor
    Junction(unsigned int id = 0);

    //Getters
    unsigned int getId() const;

    //Setters
    void setId(unsigned int id);

    friend ostream& operator<<(ostream& out, const Junction& junction);


};

//operators
bool operator<(const Junction& lhs, const Junction& rhs);
bool operator==(const Junction& lhs, const Junction& rhs);
ostream& operator<<(ostream& out, const Junction& junction);


#endif //HW03_JUNCTION_H

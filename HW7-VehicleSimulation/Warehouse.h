//
// Created by Yam Elgabsi on 11/06/2022.
//

#ifndef EX03_WAREHOUSE_H
#define EX03_WAREHOUSE_H

#include "SimObject.h"

/**
 * Warehouse class
 * is a SimObject
 * it is object with a static location with unlimited capacity of carts.
 * **/

class Warehouse: public SimObject{
private:
    int capacity;

public:
    //--The Big Five--
    Warehouse(string& name,const Point& location, int capacity): SimObject(name, location, WAREHOUSE), capacity(capacity){};
    ~Warehouse() = default;
    Warehouse(const Warehouse& other) = default;
    Warehouse(Warehouse&& other) = default;
    Warehouse& operator=(const Warehouse& other) = default;

    //--Getters--
    int getCapacity() const{ return capacity;};

    //--Setters--
    void setCapacity(int capacity);

};
using warehouse_ptr =  shared_ptr<Warehouse>;


#endif //EX03_WAREHOUSE_H

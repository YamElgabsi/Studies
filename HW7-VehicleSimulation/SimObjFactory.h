//
// Created by Yam Elgabsi on 11/06/2022.
//

#ifndef EX03_SIMOBJFACTORY_H
#define EX03_SIMOBJFACTORY_H

#include <iostream>
#include "Chopper.h"
#include "StateTrooper.h"
#include "Truck.h"
#include <memory>
#include "Warehouse.h"



using namespace std;

class SimObjFactory{
    public:
    SimObjFactory() = default;
    shared_ptr<Vehicle> create(string &name,const Point &locations, int Type);
};

#endif //EX03_SIMOBJFACTORY_H

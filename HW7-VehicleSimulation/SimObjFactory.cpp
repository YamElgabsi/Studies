//
// Created by Yam Elgabsi on 11/06/2022.
//
#include "SimObjFactory.h"

vehicle_ptr SimObjFactory::create(string& name, const Point& location, int type) {
    switch (type){
        case STATE_TROOPER:
            return make_shared<StateTrooper>(name, location);
        case CHOPPER:
            return make_shared<Chopper>(name,location);
        case TRUCK:
            return make_shared<Truck>(name,location);
        default:
            return nullptr;
    }

}


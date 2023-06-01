//
// Created by Yam Elgabsi on 11/06/2022.
//
#include "Chopper.h"

Chopper::Chopper(string &name, const Point &location): Vehicle(name,location, CHOPPER, STOPPED), attack_range(2){};


void Chopper::getStatus() {
    auto state = getState();
    if(state == COURSE) {
        cout << " Heading on course " << getCourse() << " deg, speed " << getSpeed() << " km/h" << endl;
        return;
    }

    if(state == POSITION) {
        cout << " Heading to " << getTarget() << " deg, speed " << getSpeed() << " km/h" << endl;
        return;
    }

    cout << " " << vStates_toString(state) << endl;
}
bool Chopper::attack(vehicle_ptr &truck) {
    auto _truck = dynamic_pointer_cast<Truck>(truck);
    setState(STOPPED);
    if(distance_between(*getLocation(), *_truck->getLocation()) <= attack_range && !_truck->isHaveTrooperCloser()){
        _truck->setAsRobbed();
        (attack_range < 20)? attack_range++ : attack_range;
        return true;
    }
    return false;
}

void Chopper::update(){
    auto state = getState();

    if(state == STOPPED)
        return;

    if(state == POSITION) {
        if(move(getTargetPoint()))
            setState(STOPPED);
        return;
    }
    drive(1);
}

void Chopper::setCourse(double course) {
    Vehicle::setCourse(course);
    setState(COURSE);
}






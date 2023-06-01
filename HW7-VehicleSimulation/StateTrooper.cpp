//
// Created by Yam Elgabsi on 11/06/2022.
//
#include "StateTrooper.h"

void StateTrooper::init(vector<warehouse_ptr> &whVec, shared_ptr<Warehouse> first) {
    this->firstVisit = first;
    setVisitedMap(whVec);
    nextVisit = getNextDest();
    setNextVisit(nextVisit);
    Vehicle::setSpeed(90);
}

void StateTrooper::getStatus() {
    if(getState() == COURSE)
        cout << " Heading to " << getTarget() << ", speed " << getSpeed() << "km/h" << endl;
    else if(getState() == POSITION)
        cout << " Heading to (" << getTarget() << ") , speed " << getSpeed() << "km/h" << endl;
    else
        cout << " " << vStates_toString(getState()) << endl;
}

void StateTrooper::setVisitedMap(vector<warehouse_ptr> &warehouses) {
    for(auto& warehouse : warehouses){
        visitedMap.insert(make_pair(warehouse, false));
    }
    visitedMap.at(firstVisit) = true;
}

shared_ptr<Warehouse> StateTrooper::getNextDest() {

    warehouse_ptr wh;
    bool found = false;

    getClosest(found,wh);
    if(!found){
        makeAllFalse();
        setNextVisit(firstVisit);
        return firstVisit;
    }
    setNextVisit(wh);
    return wh;
}

void StateTrooper::setNextVisit(const warehouse_ptr& warehouse) {
    setTarget(warehouse->getName());
    setCourse(angle_between(*getLocation(), *warehouse->getLocation()));
    setState(COURSE);
}

void StateTrooper::makeAllFalse() {
    for(auto& wh : visitedMap)  wh.second = false;
}

void StateTrooper::getClosest(bool &found, warehouse_ptr &currClosest) {
    double minDist = LONG_MAX;
    double dist;
    for(auto& wh: visitedMap){
        if(!wh.second){
            found = true;
            dist = distance_between(*getLocation(), *wh.first->getLocation());
            if(dist == minDist)
                if(currClosest->getName()[0] > wh.first->getName()[0]){
                    currClosest = wh.first;
                }
            if(dist < minDist) {
                minDist = dist;
                currClosest = wh.first;
            }
        }
    }
}

StateTrooper::StateTrooper(string &name, const Point &location) : Vehicle(name, location, STATE_TROOPER,STOPPED) {

}

void StateTrooper::update() {

    if (getState() == POSITION)
        if (move(getTargetPoint())) {
            nextVisit = getNextDest();
            setNextVisit(nextVisit);
            return;
        }

    if(getState() == COURSE)
        if (move(*nextVisit->getLocation())){
            nextVisit = getNextDest();
            visitedMap.at(nextVisit) = true;
            setNextVisit(nextVisit);
        }

}






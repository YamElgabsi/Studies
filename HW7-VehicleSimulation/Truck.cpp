//
// Created by Yam Elgabsi on 11/06/2022.
//
#include "Truck.h"
#include "Model.h"

void Truck::setTimes(const schedule_vector &times) {
    this->times = times;
}

shared_ptr<Warehouse> Truck::getNextWarehouse() {
  return Model::getInstance().findWareHouse(routes.at(round).first);
}

void Truck::getStatus() {
    if(getState() == MOVING_TO)
        cout << " Heading to " << routes.at(round).first << ", Crates: " << getCrates() << endl;
    else
        cout << " " + vStates_toString(getState()) << endl;
}

void Truck::setRoutes(const routes_vector &routes) {
    this->routes = routes;
    int newCrates = 0;
    for(auto &el: routes){ // calculate the all the crates.
        newCrates += el.second.second;
    }
    this->crates = newCrates;
}

void Truck::setCrates(int newCrates) {
    this->crates = newCrates;
}

bool Truck::isHaveTrooperCloser() {

  for(const auto &obj : *Model::getInstance().getSimObjects())
    if(obj->getType() == STATE_TROOPER)
      if(distance_between(*getLocation(), *obj->getLocation()) <= 10)
        return true;

  return false;
}

void Truck::setAsRobbed() {
  setCrates(0);
  setState(OFF_ROAD);
}

void Truck::motionCalculations() {
    auto wh = getNextWarehouse();
    this->setSpeed(distance_between(*getLocation(), *(*wh).getLocation()) / routes.at(round).second.first);
    setCourse(angle_between(*getLocation(), *wh->getLocation()));
}

void Truck::update() {
    if (!isMoved()) return;
    if (getState() == PARKED) {
        makeMove();
        return;
    }
    if (move(*getNextWarehouse()->getLocation())) {
        markAsArrived();
        makeMove();
    }

}

void Truck::updateInventory() {

    auto nextDest = getNextWarehouse();
    int currCrate  = routes.at(round).second.second;

    nextDest->setCapacity(nextDest->getCapacity() + currCrate);
    crates -= currCrate;
}

void Truck::markAsArrived() {
    updateInventory();
    updateIndex();
    if(isFinish())
        return;
    motionCalculations();
}

void Truck::updateIndex() {
    round++;
    if(round == routes.size()) {
        setState(OFF_ROAD);
    }
}

// if current sim Time > given time, it returns the difference else returns 0
double Truck::timeLeftToWarehouse(int time) {
    int minutes = ((time / 100) * 60) + time % 100;
    int currTimeMinutes = Model::getInstance().getGameTime() * 60;

    if(currTimeMinutes > minutes)
        return currTimeMinutes - minutes;

    return 0;
}
// true if need to move
bool Truck::isMoved() {
    if (getState() == OFF_ROAD)
        return false;

    if (getState() == PARKED)
        return isCanNotMove();

    return true;
}

// return true if object need to isCanNotMove, false otherwise.
bool Truck::isCanNotMove()
{
    double toStay = timeLeftToWarehouse(stoi(times.at(round - 1).second));
    return (toStay > 0);
}

void Truck::makeMove() {

    if(isFinish())
        return;

    //loop for going to all dests in current time
    while(willArriveInThisTime(stoi(times.at(round).first))) {
        markAsArrived();
        if(isFinish())
            return;
    }


    //if need to leave current warehouse
    if(willArriveInThisTime(stoi(times.at(round - 1).second)))
    {
        drive(timeLeftToWarehouse(stoi(times.at(round - 1).second)) / 60);
        setState(MOVING_TO);
    }
    else // if need to isCanNotMove at warehouse
    {

        setLocation(*getCurrentWarehouse()->getLocation());
        if(round == routes.size())
            setState(OFF_ROAD);
        else{
            motionCalculations();
            setState(PARKED);
        }

    }

}

bool Truck::willArriveInThisTime(int time) {
    int currTime = Model::getInstance().getGameTime();
    if(time / 100 == currTime && time % 100 == 0)   return true;
    if(time / 100 < currTime)        return true;
    return false;
}

bool Truck::isFinish()
{
    return (getState() == OFF_ROAD);
}

warehouse_ptr Truck::getCurrentWarehouse() {
    return Model::getInstance().findWareHouse(routes.at(round - 1).first);
}


//
// Created by Yam Elgabsi on 11/06/2022.
//

#include "Vehicle.h"

void Vehicle::setCourse(double course) {
    course = course;
}

void Vehicle::drive(double time) {

    double distance = time * getSpeed();
    double xCor = ((distance) * cos(toRadians(getCourse()))) / 100 + getLocation()->getX() ;
    double yCor = (distance * sin(toRadians(getCourse()))) / 100 + getLocation()->getY() ;

    setLocation(Point(xCor,yCor));
}

bool Vehicle::move(const Point &p) {
    double currDist = distance_between(*getLocation(), p);
    double coverDist = getSpeed();

    if(coverDist >= currDist){
        setLocation(p);
        return true;
    }

    drive(1);
    return false;
}

Point Vehicle::getTargetPoint()
{
    string p = getTarget();
    int xCor = stoi(p.substr(0,p.find(' ')));
    int yCor = stoi(p.substr(p.find(' '),p.size()));

    return Point(xCor,yCor);
}

void Vehicle::setSpeed(double s) { speed = s;}

void Vehicle::setState(const int s) { this->state = s;}

void Vehicle::setTarget(const string &t) { this->target = t; }

double Vehicle::getCourse() const { return course;}

double Vehicle::getSpeed() const { return speed;}

int Vehicle::getState() const { return state;}

const string &Vehicle::getTarget() const { return target; }

//
// Created by Yam Elgabsi on 11/06/2022.
//
#ifndef EX03_SIMOBJECT_H
#define EX03_SIMOBJECT_H

#include <utility>
#include <vector>
#include "Point.h"
#include "cmath"
#include <climits>
#include <memory>
#include <map>
class Model;

enum object_type{WAREHOUSE, TRUCK, STATE_TROOPER, CHOPPER};
enum vehicle_states{STOPPED, PARKED, OFF_ROAD, MOVING_TO, COURSE, POSITION};


string inline vStates_toString(int vState){
    map<int, string> mapV = { {STOPPED,"STOPPED"}, {PARKED, "PARKED"}, {OFF_ROAD,"OFF_ROAD"}, {MOVING_TO,"MOVING_TO"},
                                          {COURSE,"COURSE"}, {POSITION,"POSITION"}};
    return mapV[vState];
}


/**
 * The base class of all the object in the game simulator.
 **/
class SimObject{
private:
    string name;
    Point location;
    int type;

public:
    //--The Big Five--
    SimObject(string& name, const Point& location, int type): name(name), location(location), type(type){};
    ~SimObject() = default;
    SimObject(const SimObject& other) = default;
    SimObject(SimObject&& other) = default;
    SimObject& operator=(const SimObject& other) = default;

    //--Getters--
    int getType(){return type;};
    Point* getLocation();
    virtual const string &getName() const;

    //--Setters--
    void setLocation(const Point &location);

    //--Functions--
    void printLocation();
};

using simObject_ptr = shared_ptr<SimObject>;


#endif //EX03_SIMOBJECT_H

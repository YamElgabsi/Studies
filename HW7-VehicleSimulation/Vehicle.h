//
// Created by Yam Elgabsi on 11/06/2022.
//

#ifndef EX03_VEHICLE_H
#define EX03_VEHICLE_H

#include "SimObject.h"
#include "Warehouse.h"


/**
 * --Vehicle class--
 * Is a SimObject.
 * All the vehicle objectsToLocations in the simulator game.
 **/
class Vehicle: public SimObject{
private:
    double course;
    double speed;
    int state;
    string target;

public:
    // --The Big Five--
    Vehicle(string &name, const Point& location,int type, int state): SimObject(name, location, type), state(state), course(0), speed(0){};
    virtual ~Vehicle() = default;
    Vehicle(const Vehicle& other) = default;
    Vehicle(Vehicle&& other) = default;
    Vehicle& operator=(const Vehicle& other) = default;

    //--Getters--
    virtual void getStatus() = 0;
    virtual double getCourse() const;
    double getSpeed() const;
    const string &getTarget() const;
    int getState() const;

    //--Setters--
    virtual void setCourse(double course);
    void setSpeed(double s);
    void setState(int s);
    void setTarget(const string &t);

    //--Functions--
    virtual void drive(double time);
    virtual void update() = 0;
    virtual bool move(const Point &p);
    Point getTargetPoint();
};
using vehicle_ptr = shared_ptr<Vehicle>;


#endif //EX03_VEHICLE_H

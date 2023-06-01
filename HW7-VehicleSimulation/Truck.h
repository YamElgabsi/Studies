//
// Created by Yam Elgabsi on 11/06/2022.
//

#ifndef EX03_TRUCK_H
#define EX03_TRUCK_H

#include <vector>
#include "Vehicle.h"
using route = pair<string, pair<double, int>>; // data: < target warehouse, <time,crates>>
using schedule = pair<string,string>; // data: < arrive, leave >
using routes_vector = vector <route>; // vector of route
using schedule_vector = vector<schedule>; // vector of schedule

/**
 * --Truck class--
 * Is a Vehicle.
**/
class Truck: public Vehicle{
private:
    int crates;
    routes_vector routes;
    schedule_vector  times;
    int round;

public:
    //--The Big Five--
    Truck(string &name, const Point& location): Vehicle(name,location,TRUCK, MOVING_TO), crates(0), round(0) {};
    ~Truck() = default;
    Truck(const Truck& other) = default;
    Truck(Truck&& other) = default;
    Truck& operator=(const Truck& other) = default;

    //--Getters--
    int getCrates() const { return crates; }
    void getStatus() override;

    //--Setters--
    void setRoutes(const routes_vector &routes);
    void setTimes(const schedule_vector & times);
    void setCrates(int newCrates);
    void setAsRobbed();

    //--Functions--
    void motionCalculations();
    void update() override;

    //--Helpers Functions--
    warehouse_ptr getCurrentWarehouse();
    void markAsArrived();
    void makeMove();
    void updateInventory();
    void updateIndex();
    double timeLeftToWarehouse(int time);
    warehouse_ptr getNextWarehouse();

    //--Boolean Functions--
    bool isHaveTrooperCloser();
    bool isMoved();
    bool isCanNotMove();
    bool willArriveInThisTime(int time);
    bool isFinish();
};

#endif //EX03_TRUCK_H

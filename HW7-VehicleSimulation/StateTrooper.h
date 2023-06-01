//
// Created by Yam Elgabsi on 11/06/2022.
//

#ifndef EX03_STATETROOPER_H
#define EX03_STATETROOPER_H

#include <memory>
#include "Vehicle.h"

/**
 * --StateTrooper Class--
 * IS a Vehicle.
 **/
class StateTrooper: public Vehicle{
private:
    map<warehouse_ptr,bool> visitedMap;
    warehouse_ptr firstVisit;
    warehouse_ptr nextVisit;

public:
    // --The Big Five--
    StateTrooper(string &name, const Point& location);
    ~StateTrooper() = default;
    StateTrooper(const StateTrooper& other) = default;
    StateTrooper(StateTrooper&& other) = default;
    StateTrooper& operator=(const StateTrooper& other) = default;

    //--Getters--
    warehouse_ptr getNextDest();

    //--Setters--
    void setVisitedMap(vector<warehouse_ptr> &warehouses);
    void setNextVisit(const warehouse_ptr& warehouse);


    //--Functions--
    void getStatus();
    void init(vector<warehouse_ptr> &whVec, shared_ptr<Warehouse> first);
    void makeAllFalse();
    void getClosest(bool &found, warehouse_ptr &currCloses);
    void update();


};

#endif //EX03_STATETROOPER_H

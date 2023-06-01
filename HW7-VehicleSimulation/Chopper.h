//
// Created by Yam Elgabsi on 11/06/2022.
//
#ifndef EX03_CHOPPER_H
#define EX03_CHOPPER_H

#include "SimObject.h"
#include "Vehicle.h"
#include "Truck.h"

class Truck;

/**
 * --Chopper Class--
 **/
class Chopper: public Vehicle{
private:
    int attack_range;

public:
    //--The Big Five--
    Chopper(string &name, const Point& location);
    ~Chopper() override = default;
    Chopper(const Chopper& other) = default;
    Chopper(Chopper&& other) = default;
    Chopper& operator=(const Chopper& other) = default;

    //--Getters--
    void getStatus() override;

    //--Setters--
    void setCourse(double course) override;

    //--Functions--
    bool attack(vehicle_ptr& truck);
    void update() override;
};


#endif //EX03_CHOPPER_H

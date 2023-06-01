//
// Created by YamEl on 12/15/2021.
//

#ifndef HW03_METROPOLIS_H
#define HW03_METROPOLIS_H

#include "Junction.h"
#include "Road.h"
#include "Map.h"
#include "Cars.h"



using namespace std;

const int max_junctions = 500;
const int max_cars = 10000;


class Metropolis {
private:
    int size;
    Road** roads;
    Junction* junctions;
    Car** cars; // list of pointer to car
    Map<string,int> map; // <car_name,junction_id>
    int carCounter;


public:
    /*Big Three:
    //the Big Three does not have implementation because the default one is good enough(int)
    */
    ~Metropolis();

    //Constructor
    Metropolis(double** graph, unsigned int size);

    //Getters
    int getSize() const;
    Road **getRoads() const;
    Junction *getJunctions() const;
    Car **getCars() const;

    int getCarLocation(string car);

    //Setters

    //functions in the Metropolis
    void moveALL(int time = 0);
    void printRoads();
    void printRoadsAir();
    void printJunctions();

    //Helper_functions
    unsigned int options(int junctionID);
    void setNewCar(int junctionID, int type);
    void moveCar(int carId, int fromJunction, int toJunction);
    void makeMoveRandomly(int carId);
};



#endif //HW03_METROPOLIS_H

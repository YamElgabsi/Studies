//
// Created by YamEl on 12/15/2021.
//

#ifndef HW03_METROPOLIS_H
#define HW03_METROPOLIS_H

#include "Junction.h"
#include "Road.h"
#include "Car.h"


using namespace std;

const int max_junctions = 500;
const int max_cars = 10000;






class Metropolis {
private:
    int size;
    Road** roads;
    Junction* junctions;
    Car** cars; // list of pointer to car
    double c;


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
    double getC() const;
    int carCounter;

    //Setters
    void setC(double c);

    //functions in the Metropolis

    void moveALL(int time = 0);
    void printRoads();
    void printRoadsAir();
    void printJunctions();

    //Helper_functions
    void setNewCar(int junctionID);
    void moveCar(int carId, int fromJunction, int toJunction);
    void makeMoveRandomly(int carId);
};



#endif //HW03_METROPOLIS_H

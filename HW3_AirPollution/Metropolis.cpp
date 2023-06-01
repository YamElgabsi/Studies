//
// Created by YamEl on 12/15/2021.
//

#include "Metropolis.h"

//Big three:
Metropolis::~Metropolis() {
    for(int i = 0; i < size; i++)
        delete [] roads[i];
    delete [] roads;
    delete [] junctions;
    for(int i = 0; i < max_cars; i++)
        delete [] cars[i];

}

//Constructor
Metropolis::Metropolis(double **graph, unsigned int size) :size(size), c(0), carCounter(0) {
    srand ( time(NULL) ); // for future random use
    roads = new Road*[this->size];
    for (int i = 0; i < this->size; i++){
        roads[i] = new Road[this->size];
        for (int j = 0; j < this->size; ++j) {
            roads[i][j] = Road(i,j,graph[i][j]);
        }
    }
    junctions = new Junction[max_junctions];
    for (int i = 0; i < max_junctions; ++i)
        junctions[i] = Junction(i);

    cars = new Car*[max_cars];
    for (int i = 0; i < max_cars; ++i)
        cars[i] = new Car(i);
}

int Metropolis::getSize() const {
    return size;
}

Road **Metropolis::getRoads() const {
    return roads;
}

Junction *Metropolis::getJunctions() const {
    return junctions;
}

Car **Metropolis::getCars() const {
    return cars;
}

double Metropolis::getC() const {
    return c;
}

void Metropolis::setC(double c) {
    Metropolis::c = c;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            roads[i][j].setC(c);

        }

    }
}

void Metropolis::moveALL(int time) {
    for (int i = 0; i < time; ++i) {
        for (int j = 0; j < carCounter; ++j) {
            makeMoveRandomly(j);

        }

    }
}

void Metropolis::printRoads() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << roads[i][j];

        }
        cout << endl;

    }
}

void Metropolis::printRoadsAir() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << double2STR(roads[i][j].getAirPollution()) << " ";

        }
        cout << endl;

    }
}



void Metropolis::printJunctions() {
    for (int i = 0; i < size; ++i) {
        cout << junctions[i] << endl;

    }
}

//Helper_functions:
void Metropolis::setNewCar(int junctionID) {
    cars[carCounter]->setLocation(junctionID);
    junctions[junctionID].insertCar(*cars[carCounter]);
    carCounter++;
}
void Metropolis::moveCar(int carId, int fromJunction, int toJunction) {
    if (fromJunction == toJunction)
        return; //stay in place
    junctions[fromJunction].removeCar(carId);
    junctions[toJunction].insertCar(carId);
    roads[fromJunction][toJunction]++;
    cars[carId]->setLocation(toJunction);
}

void Metropolis::makeMoveRandomly(int carId) {
    int counter = 0;
    int currentPlace = cars[carId]->getLocation();
    for (int i = 0; i < size; ++i) {// check how many choice the car have
        if (i == currentPlace || roads[currentPlace][i].getLength() != 0.0)
            counter++;
    }
    int choice = (rand() % counter) +1; // generate random number between 1 and number of choices
    int j = 0;
    for (int i = 0; i <= size; ++i) {
        if (i == currentPlace || roads[currentPlace][i].getLength() != 0.0)
            j++;
        if(choice == j){
            moveCar(carId,currentPlace,i);
            return;
        }
    }

}



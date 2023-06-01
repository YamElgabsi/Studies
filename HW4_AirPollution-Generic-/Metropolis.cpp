//
// Created by YamEl on 12/15/2021.
//

#include "Metropolis.h"

int Metropolis::getCarLocation(string car) {
    return *map[car];
}

//Big three:
Metropolis::~Metropolis() {
    for(int i = 0; i < size; i++)
        delete [] roads[i];
    delete [] roads;
    delete [] junctions;
    for(int i = 0; i < carCounter; i++)
        delete cars[i];
    delete [] cars;



}

//Constructor
Metropolis::Metropolis(double **graph, unsigned int size) :size(size), carCounter(0) {
    srand ( time(NULL) ); // for future random use
    roads = new Road*[this->size];
    for (int i = 0; i < this->size; i++){
        roads[i] = new Road[this->size];
        for (int j = 0; j < this->size; ++j) {
            roads[i][j] = Road(i+1,j+1,graph[i][j]);
        }
    }
    junctions = new Junction[max_junctions];
    for (int i = 0; i < max_junctions; ++i) {
        junctions[i] = Junction(i+1);
    }

    cars = new Car*[max_cars];
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


void Metropolis::moveALL(int time) {
    for (int i = 0; i < time; ++i) {
        for (int j = 0; j < carCounter; ++j) {
            makeMoveRandomly(j+1);
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
            if (j != 0)
                cout << " ";
            cout << double2STR(roads[i][j].getTotalAirPollution());
        }
        cout << endl;
    }
}



void Metropolis::printJunctions() {
    for (int i = 0; i < size; i++) {
        cout << junctions[i] << ":";
        for (int j = 0; j < carCounter; j++) {
            if (cars[j]->getLocation() == i+1) {
                cout << " ";
                cout << cars[j]->getName();
            }
        }
        cout<<endl;
    }


}

//Helper_functions:
unsigned int Metropolis::options(int junctionID) {
    int counter = 0;
    for (int i = 0; i < size; i++ ){
        if ((roads[junctionID-1][i].getLength() != 0) && ( i!= (int)(junctionID-1)))
            counter++;
    }
    return counter;    
}

void Metropolis::setNewCar(int junctionID, int type) {
    switch (type) {
        case FAMILY: 
            cars[carCounter] = new FamilyCar(carCounter+1, junctionID);
            break;
        case LUXURY:
            cars[carCounter] = new LuxuryCar(carCounter+1, junctionID);
            break;
        case SPORTS:
            cars[carCounter] = new SportsCar(carCounter+1, junctionID);
            break;
        case MASERATI:
            cars[carCounter] = new Maserati(carCounter+1, junctionID);
            break;
    }
    map.insert(cars[carCounter]->getName(),junctionID);
    carCounter++;
}

void Metropolis::moveCar(int carId, int fromJunction, int toJunction) {
    if (fromJunction == toJunction)
        return; //stay in place
    map.insert(cars[carId-1]->getName(),toJunction);
    roads[fromJunction-1][toJunction-1]+= *cars[carId-1];
    cars[carId-1]->setLocation(toJunction);
}


void Metropolis::makeMoveRandomly(int carId) {
    int currentPlace = cars[carId-1]->getLocation();
    int numberOfOptions = options(currentPlace);
    int type = cars[carId-1]->getType();
    int p = numberOfOptions;
    switch (type) {//add options to stay in current junctions
        case FAMILY:{
            p+=1;
            break;
        }
        case LUXURY: {
            p += numberOfOptions;
            break;
        }
    }
    if (p == 0)
        return;// stay in place
    
    
    int choice = (rand() % p) +1; // generate random number between 1 and number of choices
    if (choice > numberOfOptions)// stay in place
        return;
    int j = 0;
    for (int i = 0; i <= size; ++i) {
        if (i+1 != currentPlace && roads[currentPlace-1][i].getLength() != 0.0)
            j++;
        if(choice == j){
            moveCar(carId,currentPlace,i+1);
            return;
        }
    }

}



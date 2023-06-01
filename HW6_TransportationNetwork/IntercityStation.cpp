//
// Created by YamEl on 5/20/2022.
//

#include "IntercityStation.h"

IntercityStation::IntercityStation(string name): Station(INTERCITY,name) {

}

void IntercityStation::printID() const {
    cout << "Intercity Station " << Station::get_name() <<" #" << Station::getId();
}



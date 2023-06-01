//
// Created by YamEl on 5/20/2022.
//

#include "StadStation.h"

StadStation::StadStation(string name): Station(STAD,name) {

}

void StadStation::printID() const {
    cout << "Stad Station " << Station::get_name() <<" #" << Station::getId();
}
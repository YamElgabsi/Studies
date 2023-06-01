//
// Created by YamEl on 5/20/2022.
//

#include "CentraalStation.h"


CentraalStation::CentraalStation(string name): Station(CENTRAAL,name) {

}

void CentraalStation::printID() const {
    cout << "Centraal Station " << Station::get_name() <<" #" << Station::getId();
}

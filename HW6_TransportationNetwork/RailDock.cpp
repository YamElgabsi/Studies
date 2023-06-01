//
// Created by YamEl on 5/20/2022.
//

#include "RailDock.h"

RailDock::RailDock(): Dock(RAIL) {

}

void RailDock::printID() const {
    cout<<"R"<<this->getId();
}

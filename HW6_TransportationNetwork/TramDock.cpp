//
// Created by YamEl on 5/20/2022.
//

#include "TramDock.h"

TramDock::TramDock(): Dock(TRAM) {

}

void TramDock::printID() const {
    cout<<"B" << this->getId();
}

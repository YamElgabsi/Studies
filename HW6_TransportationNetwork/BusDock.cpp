//
// Created by YamEl on 5/20/2022.
//

#include "BusDock.h"

BusDock::BusDock(): Dock(BUS) {

}

void BusDock::printID() const {
    cout<<"B" << this->getId();
}

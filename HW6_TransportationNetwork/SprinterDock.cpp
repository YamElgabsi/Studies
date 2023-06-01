//
// Created by YamEl on 5/20/2022.
//

#include "SprinterDock.h"

SprinterDock::SprinterDock(): Dock(SPRINTER){

}

void SprinterDock::printID() const {
    cout <<"S"<< this->getId();
}

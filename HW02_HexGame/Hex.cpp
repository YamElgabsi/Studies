//
// Created by YamEl on 11/26/2021.
//

#include "Hex.h"
#include <string>
#include <sstream>

Hex::Hex() {
    color = EMPTY;
    visited = false;
}

//getters and setters
int Hex::getColor() const {
    return color;
}
void Hex::setColorBlue() {
    this->color = BLUE;
}
void Hex::setColorRed(){
    this->color = RED;
}

bool Hex::isEmpty() const {
    return color==EMPTY;
}
bool Hex::isBlue() const {
    return color==BLUE;
}
bool Hex::isRed() const {
    return color==RED;
}


bool Hex::isVisited() const {
    return visited;
}
void Hex::turnFalse() {
    visited = false;
}
void Hex::turnTrue() {
    visited = true;
}

char Hex::toChar() {
    if (getColor() == EMPTY)
        return 'O';
    if (getColor() == BLUE)
        return 'B';
    return 'R';
}

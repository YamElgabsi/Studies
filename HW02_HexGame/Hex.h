//
// Created by YamEl on 11/26/2021.
//

#ifndef HW02_HEX_H
#define HW02_HEX_H

#include "iostream"
using namespace std;
enum mode{EMPTY = 0, BLUE = 1, RED = 2};

class Hex {
private:
    int color;
    bool visited;

public:
    Hex();

    //getters and setters
    int getColor() const;
    void setColorBlue();
    void setColorRed();

    bool isEmpty() const;
    bool isBlue() const;
    bool isRed() const;

    bool isVisited() const;
    void turnTrue();
    void turnFalse();

    char toChar();

};


#endif //HW02_HEX_H

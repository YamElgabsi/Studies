//
// Created by Yam Elgabsi on 11/06/2022.
//


#include "View.h"

void View::show() const {
    int counter = 0;
    printInfo();

    for(int y = int(this->Y + this->size * this->scale - this->scale); y >= this->Y; y-= int(this->scale)) {
        cout << setw(5);
        if (counter == 0)   drawLineBegin(y);
        else    cout << setw(7);
        for(int corX = this->X; corX <= this->size * this->scale + X - this->scale; corX += int(this->scale)) printP(corX, y);
        cout << endl;
        counter == 2 ? counter = 0 : counter++;
    }
    counter = 0;
    for(int corX = this->X; corX <= this->size * this->scale + this->X - this->scale; corX += int(this->scale))
    {
        if(!counter)    cout << setw(6)<< corX;
        counter == 2 ? counter = 0 : counter++;
    }
    cout << endl;
}

void View::drawLineBegin(int cor) {
    cout << cor;

    if(to_string(cor).size() == 3)
        cout << setw(1);
    else
        cout << setw(2);
}

void View::printInfo() const{
    cout << "Scale: " << getScale() << " | Origin: (" << to_string(getX()) << ", " << to_string(getY()) << ")" << endl;
}

void View::printP(int x, int y) const {
    if(this->objectLocations.find({x, y}) == this->objectLocations.end()){
        cout << ". ";
        return;
    }
    cout << this->objectLocations.at({x, y});
}

double View::getScale() const {
    return this->scale;
}

void View::setScale(double scale) {
    this->scale = scale;
}


void View::setSize(int size) {
    this->size = size;
}

int View::getX() const {
    return this->X;
}

void View::setX(int x0) {
    this->X = x0;
}

int View::getY() const {
    return this->Y;
}

void View::setY(int y0) {
    this->Y = y0;
}

void View::update() {
    this->objectLocations.clear();
    int x,y;
    string name;

    for(const auto& obj:*(this->model).getSimObjects())
    {
        Point& p = *obj->getLocation();
        x = (int) p.getX();
        y = (int) p.getY();
        x -= x % ((int) this->scale);
        y -= y % ((int) this->scale);
        name = obj->getName().substr(0,2);
        this->objectLocations.insert({{x, y}, name});
    }
}



void View::setDefault() {
    this->setX(-10);
    this->setY(-10);
    this->setSize(25);
    this->setScale(2.00);
}



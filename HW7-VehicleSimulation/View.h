//
// Created by Yam Elgabsi on 11/06/2022.
//


#ifndef EX03_VIEW_H
#define EX03_VIEW_H

#include <iostream>
#include "map"
#include "Model.h"
#include <iomanip>

using namespace std;

class View{
private:
    double scale;
    int size;
    int X;
    int Y;
    map<pair<int,int>,string> objectLocations;
    Model& model;


public:
    //--The Big Five--
    View(): scale(2.0), size(25), X(-10), Y(-10), model(Model::getInstance()){};
    ~View() = default;
    View(const View& other) = default;
    View(View&& other) = default;
    View& operator=(const View& other) = delete;

    //--Getters--
    double getScale() const;
    int getX() const;
    int getY() const;

    //--Setters--
    void setScale(double scale);
    void setSize(int size);
    void setX(int x0);
    void setY(int y0);
    void setDefault();

    //--Functions--
    void show() const;
    void update();
    void printP(int x, int y) const;
    static void drawLineBegin(int cor) ;
    void printInfo() const;

};
using view_ptr = shared_ptr<View>;

#endif //EX03_VIEW_H
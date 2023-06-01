//
// Created by YamEl on 12/15/2021.
//

#ifndef HW03_ROAD_H
#define HW03_ROAD_H

#include <cstdlib>
#include <sstream>
#include "string"
#include <iostream>
#include <cstring>
#include <iomanip>
#include <ctime>

using namespace std;
inline int precision(float x){
    int x_int(x);
    if (x - x_int == 0.0)
        return 0;
    return 2;
}
void remove_after_dots(string &str);
inline string double2STR(double c){
    if (c == 0)
        return "0";
    stringstream data;
    string str;
    data<<fixed<<setprecision(precision(c))<<c;
    data >> str;
    remove_after_dots(str);
    return str;
}

class Road {
private:
    int fromJunction;
    int toJunction;
    double length;
    double airPollution;
    double c;

public:
    //the Big Three does not have implementation because the default one is good enough(int and double)

    //Constructor
    Road(int fromJunction = -1, int toJunction = -1, double length = 0.0, double c = 0.0);

    //Getters
    int getFromJunction() const;
    int getToJunction() const;
    double getLength() const;
    double getAirPollution() const;
    double getC() const;

    //Setters
    void setFromJunction(int fromJunction);
    void setToJunction(int toJunction);
    void setLength(double length);
    void setC(double c);
    const Road& operator++();
    const Road& operator++(int);

    friend ostream& operator<<(ostream& out, const Road& road);


};
ostream& operator<<(ostream& out, const Road& road);



#endif //HW03_ROAD_H

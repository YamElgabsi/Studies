//
// Created by YamEl on 6/3/2022.
//

#ifndef EX03_POINT_H
#define EX03_POINT_H

#include "iostream"
#include "cmath"
#include <sstream>
#include <stdexcept>

using namespace std;

#define pai 3.141592653589793

double toRadians(double angle);
double toDegrees(double angle);

/**
 * A point in the plane.
 * */
class Point {
private:
    double x;
    double y;

public:
    //--The Big Five--
    Point();
    Point(pair<double,double> pair);
    Point(double x, double y, bool isPolar = false);
    ~Point() = default;
    Point(const Point& other) = default;
    Point& operator=(const Point& other) = default;
    Point(const Point&& other);

    //--Getters--
    double getX() const;
    double getY() const;
    double getRadius() const;
    double getAngle() const;
    pair<double,double> getCartesianPoint() const;
    pair<double,double> getPolarPoint() const;

    //--Setters--
    void setX(double x);
    void setY(double y);
    void setPoint(double x, double y);
    void setRadius(double radius);
    void setAngle(double angle);
    void updateXY(double x, double y);
    void updateByPolar(double radius, double angle);

    //--Comparators--
    bool operator==(const Point &rhs) const;
    bool operator!=(const Point &rhs) const;
    bool operator==(const pair<double,double> &rhs) const;
    bool operator!=(const pair<double,double> &rhs) const;

    //--Operators--
    friend ostream &operator<<(ostream &os, const Point &point);
    Point& operator+=(const Point& rhs);
    const Point operator+(const Point &other) const;
    Point& operator-=(const Point& rhs);
    const Point operator-(const Point &other) const;
};


double distance_between(const Point& p1, const Point& p2);
double time_FPTP(Point& from, Point& to, double kmph);
double angle_between(const Point& p1, const Point& p2);




#endif //EX03_POINT_H

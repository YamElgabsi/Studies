//
// Created by YamEl on 6/3/2022.
//

#include "Point.h"

/**
 * Default Point is (0,0).
 * */
Point::Point():x(0), y(0) {}

/**
* @param x   if polar is radius.
* @param y   if polar is angel.
* */
Point::Point(double x, double y, bool isPolar):x(x), y(y) {
    if (isPolar){
        if (y < 0.0) throw invalid_argument("Radius can not be negative!\n");

        y = fmod(y,360); // y = y(mod360)
        if (y < 0)  y = 360 + y;

        this->x = x * cos(y);
        this->y = x * sin(y);
    }
}

Point::Point(const Point &&other) {
    this->x = other.x;
    this->y = other.y;
}

double Point::getX() const {
    return x;
}

void Point::setX(double x) {
    Point::x = x;
}

double Point::getY() const {
    return y;
}

void Point::setY(double y) {
    Point::y = y;
}

double Point::getRadius() const {
    return sqrt(x*x + y*y);
}

double Point::getAngle() const {
    if (x == 0){
        if(y == 0)  return 0.0;
        if (y < 0)  return 270.0;
        return 90.0;
    }
    return atan(y/x);
}

void Point::setRadius(double radius) {
    if (radius < 0) throw invalid_argument("Radius can not be negative!\n");

    double angle = getAngle();

    this->x = radius * cos(angle);
    this->y = radius * sin(angle);
}

void Point::setAngle(double angle) {
    angle = fmod(angle,360); // angle = angle(mod360)
    if (angle < 0)  angle = 360 + angle;

    double radius = getRadius();

    this->x = radius * cos(angle);
    this->y = radius * sin(angle);
}

bool Point::operator==(const Point &rhs) const {
    return ((x == rhs.x) && (y == rhs.y));
}

bool Point::operator!=(const Point &rhs) const {
    return !(rhs == *this);
}

bool Point::operator==(const pair<double, double> &rhs) const {
    return ((x == rhs.first) && (y == rhs.second));
}

bool Point::operator!=(const pair<double, double> &rhs) const {
    return !(*this == rhs);
}

ostream &operator<<(ostream &os, const Point &point) {
    os << "(" << point.x << "," << point.y << ")";
    return os;
}

pair<double, double> Point::getCartesianPoint() const{
    return {x, y};
}

Point::Point(pair<double, double> pair):x(pair.first), y(pair.second) {
}

pair<double, double> Point::getPolarPoint() const {
    return {getRadius(),getAngle()};
}

void Point::updateXY(double x, double y) {
    this->x += x;
    this->y += y;
}

void Point::updateByPolar(double radius, double angle) {
    if (radius < 0) throw invalid_argument("Radius can not be negative!\n");
    if (radius == 0) return;

    angle = fmod(angle,360); // angle = angle(mod360)
    if (angle < 0)  angle = 360 + angle;

    double x_ = radius * cos(angle);
    double y_ = radius * sin(angle);

    updateXY(x_,y_);
}

void Point::setPoint(double x, double y) {
    this->x = x;
    this->y = y;
}

Point& Point::operator+=(const Point &rhs) {
    this->x += rhs.x;
    this->y += rhs.y;

    return *this;
}


const Point Point::operator+(const Point &other) const {
    return Point(*this) += other;
}

Point &Point::operator-=(const Point &rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;

    return *this;
}

const Point Point::operator-(const Point &other) const {
    return Point(*this) -= other;
}

double distance_between(const Point& p1,const Point& p2){
    return sqrt((p1.getX() - p2 .getX())*(p1.getX() - p2 .getX()) + (p1.getY() - p2 .getY())*(p1.getY() - p2 .getY()));
}

double toRadians(double angle)
{
    return angle * pai / 180.0;
}

double toDegrees(double angle)
{
    return angle * 180.0 / pai;
}

double angle_between(const Point& p1,const Point& p2) {
    return atan2(p2.getY() - p1.getY(), p2.getX() - p1.getX()) * 180 / pai;
}





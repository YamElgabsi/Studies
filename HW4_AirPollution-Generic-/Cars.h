//
// Created by YamEl on 1/1/2022.
//

#ifndef HW04_CARS_H
#define HW04_CARS_H
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

enum carType{FAMILY, SPORTS, LUXURY, MASERATI};

class Car {
private:
    string name;
    unsigned int id;
    unsigned int location; //junction_id

public:
    //Big Three:
    /*
    Car(const Car& other);
    Car& operator=(const Car& rhs);
*/
    virtual ~Car(){}
    //Constructor
    Car(unsigned int id = 0, unsigned int location = 0, char type = 'D');

    //Getters
    int getId() const;
    int getLocation() const;
    const string& getName() const;
    virtual int getType() const = 0;

    //Setters
    void setId(int id);
    void setLocation(int location);

    virtual unsigned int getAirPollution() const = 0;
    virtual string toString() const = 0;

};

class FamilyCar : virtual public Car{
private:

public:
    //Big Three: does not have implication because the default is good enough
    virtual ~FamilyCar(){}

    //Constructor
    FamilyCar(unsigned int id = 0, unsigned int location = 0): Car(id,location,'F'){}

    virtual int getType() const{return FAMILY;}

    virtual unsigned int getAirPollution() const;
    virtual string toString() const;

};


class LuxuryCar : virtual public Car{
private:

public:
    //Big Three: does not have implication because the default is good enough
    virtual ~LuxuryCar(){}

    //Constructor
    LuxuryCar(unsigned int id = 0, unsigned int location = 0): Car(id,location,'L'){}

    virtual int getType() const{return LUXURY;}
    virtual unsigned int getAirPollution() const;
    virtual string toString() const;

};


class SportsCar : virtual public Car{
private:

public:
    //Big Three: does not have implication because the default is good enough
    virtual ~SportsCar(){}

    //Constructor
    SportsCar(unsigned int id = 0, unsigned int location = 0): Car(id,location,'S'){}

    virtual int getType() const{return SPORTS;}
    virtual unsigned int getAirPollution() const;
    virtual string toString() const;

};


class Maserati : public SportsCar, public  LuxuryCar{
private:

public:
    //Big Three: does not have implication because the default is good enough
    virtual ~Maserati(){}

    //Constructor
    Maserati(unsigned int id = 0, unsigned int location = 0): Car(id, location,'M'){}

    virtual int getType() const{return MASERATI;}
    virtual unsigned int getAirPollution() const;
    virtual string toString() const;

};


//operators
bool operator<(const Car& lhs, const Car& rhs);
bool operator==(const Car& lhs, const Car& rhs);
ostream& operator<<(ostream& out, const Car& car);
ostream& operator<<(ostream& out, const SportsCar& sportsCar);
ostream& operator<<(ostream& out, const LuxuryCar& luxuryCar);
ostream& operator<<(ostream& out, const FamilyCar& familyCar);
ostream& operator<<(ostream& out, const Maserati& maserati);


#endif //HW04_CARS_H

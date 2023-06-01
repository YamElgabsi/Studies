//
// Created by YamEl on 5/17/2022.
//

#ifndef HW02_DOCK_H
#define HW02_DOCK_H
#include <iostream>
#include <memory>

class Station;

using namespace std;

enum dock_types{BUS = 0, TRAM = 1, SPRINTER = 2, RAIL = 3, ALL = 4};

string inline dock_types2name(int type){
    switch (type) {
        case BUS:
            return "bus";
        case TRAM:
            return "tram";
        case SPRINTER:
            return "sprinter";
        case RAIL:
            return "rail";

    }
    return "all";
}

class Dock {
private:
    //--ID--:
    int type;
    const int id;
    static int dock_counter;//for constructors
public:
    //--The Big Five--:
    Dock(int type);
    Dock() = delete;
    ~Dock() = default;
    Dock(const Dock& other) = delete;
    Dock& operator=(const Dock& other) = delete;
    Dock(const Dock&& other) = delete;

    //--Getters--
    int getType() const;
    int getId() const;

    //--Prints--
    virtual void printID() const = 0;

    //--Operators--
    bool operator==(const Dock &rhs) const;
    bool operator!=(const Dock &rhs) const;
};


#endif //HW02_DOCK_H

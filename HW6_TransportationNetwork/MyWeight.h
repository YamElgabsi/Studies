//
// Created by YamEl on 5/20/2022.
//

#ifndef HW02_MYWEIGHT_H
#define HW02_MYWEIGHT_H

#include "iostream"
using namespace std;

class MyWeight {
private:
    int time; // in minutes. not unsigned because the graph
    static bool weighted;

public:
    //--The Big Five--:
    MyWeight(int time = 1);
    ~MyWeight() = default;
    MyWeight(const MyWeight& other) = default;
    MyWeight& operator=(const MyWeight& other) = default;
    MyWeight(const MyWeight&& other);

    // --Setters--
    void setTime(int time);
    void makeWeighted();
    void makeUnWeighted();

    //--Getters--
    bool isWeighted() const;
    int getWeight() const;
    double getHour() const;

    //--Comparators--
    bool operator==(const MyWeight &rhs) const;
    bool operator!=(const MyWeight &rhs) const;
    bool operator<(const MyWeight &rhs) const;
    bool operator>(const MyWeight &rhs) const;
    bool operator<=(const MyWeight &rhs) const;
    bool operator>=(const MyWeight &rhs) const;


    friend ostream &operator<<(ostream &os, const MyWeight &weight);
};


#endif //HW02_MYWEIGHT_H

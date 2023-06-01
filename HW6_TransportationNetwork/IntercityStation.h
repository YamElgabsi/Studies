//
// Created by YamEl on 5/20/2022.
//

#ifndef HW02_INTERCITYSTATION_H
#define HW02_INTERCITYSTATION_H

#include "Station.h"

class IntercityStation : public Station{

public:
    //--The Big Five--:
    IntercityStation(string name = "NO NAME");
    virtual ~IntercityStation() = default;
    IntercityStation(const IntercityStation& other) = delete;
    IntercityStation& operator=(const IntercityStation& other) = delete;
    IntercityStation(const IntercityStation&& other) = delete;

    void printID() const override;

};


#endif //HW02_INTERCITYSTATION_H

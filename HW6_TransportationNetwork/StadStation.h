//
// Created by YamEl on 5/20/2022.
//

#ifndef HW02_STADSTATION_H
#define HW02_STADSTATION_H

#include "Station.h"

class StadStation : public Station{

public:
    //--The Big Five--:
    StadStation(string name = "NO NAME");
    virtual ~StadStation() = default;
    StadStation(const StadStation& other) = delete;
    StadStation& operator=(const StadStation& other) = delete;
    StadStation(const StadStation&& other) = delete;

    void printID() const override;

};


#endif //HW02_STADSTATION_H

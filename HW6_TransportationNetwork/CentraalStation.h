//
// Created by YamEl on 5/20/2022.
//

#ifndef HW02_CENTRAALSTATION_H
#define HW02_CENTRAALSTATION_H

#include "Station.h"

class CentraalStation : public Station{

public:
    //--The Big Five--:
    CentraalStation(string name = "NO NAME");
    virtual ~CentraalStation() = default;
    CentraalStation(const CentraalStation& other) = delete;
    CentraalStation& operator=(const CentraalStation& other) = delete;
    CentraalStation(const CentraalStation&& other) = delete;

    void printID() const override;

};

#endif //HW02_CENTRAALSTATION_H

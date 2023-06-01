//
// Created by YamEl on 5/20/2022.
//

#ifndef HW02_TRAMDOCK_H
#define HW02_TRAMDOCK_H

#include "Dock.h"

class TramDock : public Dock{
private:

public:
    //--The Big Five--:
    TramDock();
    ~TramDock() = default;
    TramDock(const TramDock& other) = delete;
    TramDock& operator=(const TramDock& other) = delete;
    TramDock(const TramDock&& other) = delete;

    void printID() const override;

};


#endif //HW02_TRAMDOCK_H

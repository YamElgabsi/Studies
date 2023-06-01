//
// Created by YamEl on 5/20/2022.
//

#ifndef HW02_RAILDOCK_H
#define HW02_RAILDOCK_H

#include "Dock.h"

class RailDock : public Dock{
private:

public:
    //--The Big Five--:
    RailDock();
    ~RailDock() = default;
    RailDock(const RailDock& other) = delete;
    RailDock& operator=(const RailDock& other) = delete;
    RailDock(const RailDock&& other) = delete;

    void printID() const override;

};


#endif //HW02_RAILDOCK_H

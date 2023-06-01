//
// Created by YamEl on 5/20/2022.
//

#ifndef HW02_SPRINTERDOCK_H
#define HW02_SPRINTERDOCK_H

#include "Dock.h"

class SprinterDock : public Dock{
private:

public:
    //--The Big Five--:
    SprinterDock();
    ~SprinterDock() = default;
    SprinterDock(const SprinterDock& other) = delete;
    SprinterDock& operator=(const SprinterDock& other) = delete;
    SprinterDock(const SprinterDock&& other) = delete;

    void printID() const override;

};


#endif //HW02_SPRINTERDOCK_H

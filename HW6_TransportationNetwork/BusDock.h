//
// Created by YamEl on 5/20/2022.
//

#ifndef HW02_BUSDOCK_H
#define HW02_BUSDOCK_H

#include "Dock.h"

class BusDock : public Dock{
private:

public:
    //--The Big Five--:
    BusDock();
    ~BusDock() = default;
    BusDock(const BusDock& other) = delete;
    BusDock& operator=(const BusDock& other) = delete;
    BusDock(const BusDock&& other) = delete;

    void printID() const override;

};


#endif //HW02_BUSDOCK_H

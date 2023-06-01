//
// Created by YamEl on 4/19/2022.
//

#ifndef HW1_DELTA_H
#define HW1_DELTA_H

#include "SARS_CoV_2.h"

class Delta : public SARS_CoV_2{
public:
    //Constructor & Destructor
    Delta(const vector<char> &dna, int dim, SARS_CoV_2 *ancestor = NULL);

    //Updates
    void personalChange() override;

    //Prints
    void printStrain() override;

};


#endif //HW1_DELTA_H

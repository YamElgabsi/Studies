//
// Created by YamEl on 4/19/2022.
//

#ifndef HW1_THEWORLDOFVIRUSES_H
#define HW1_THEWORLDOFVIRUSES_H

#include "Alpha.h"
#include "Omicron.h"
#include "Delta.h"

class TheWorldOfViruses {
private:
    int dim;
    int gen = 0;
    int max_gen;

    vector<SARS_CoV_2* > ancestors;
    vector<SARS_CoV_2* > viruses;
    vector<char> target;

public:
    //Constructor & Destructor
    TheWorldOfViruses(int dim, int maxGen, const vector<SARS_CoV_2 *> &ancestors, const vector<char> &target);

    //Getters
    int getDim() const;
    int getGen() const;
    int getMaxGen() const;

    //Updates
    void updatePowers();
    void personal_change_to_all();
    void groupChange();
    bool sim_gen(); // return if succeed
    bool is_one();
    void sim_to_end();



    void print();
};


#endif //HW1_THEWORLDOFVIRUSES_H

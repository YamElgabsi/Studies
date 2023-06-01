//
// Created by YamEl on 4/19/2022.
//

#ifndef HW1_SIMULATOR_H
#define HW1_SIMULATOR_H

#include "TheWorldOfViruses.h"
inline bool isBase(char ch){
    return (ch == 'A' || ch == 'C' || ch == 'T' || ch == 'G');
}

inline bool isCorona(char ch){
    return (ch == 'a' || ch == 'd' || ch == 'o');
}

void raise_error();

bool is_number(const string& s);

int run(int argc, char** argv);

bool read_config_file(vector<string>& config_data, int& dim, vector<char>& target, int& max_gen);

bool read_first_generation_file(vector<string>& first_generation_data, vector<SARS_CoV_2 *> &ancestors, int& dim, int& num_of_viruses);



#endif //HW1_SIMULATOR_H

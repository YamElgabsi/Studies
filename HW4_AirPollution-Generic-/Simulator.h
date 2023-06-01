//
// Created by YamEl on 12/17/2021.
//

#ifndef HW03_SIMULATOR_H
#define HW03_SIMULATOR_H

#include "Metropolis.h"
#include <fstream>
#include <cstdlib>
#include <string>

void error(string output = "ERROR: Invalid input.");
void removeTypeFromString(string& str);
void char2int(char& ch, int& intR);
void string2int(string& str, int& intR);
void string2double(string& string, double& doubleR);
void simMetropolisFromFile(int argc, char* argv[]);




#endif //HW03_SIMULATOR_H

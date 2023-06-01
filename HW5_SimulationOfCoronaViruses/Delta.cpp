//
// Created by YamEl on 4/19/2022.
//

#include "Delta.h"

Delta::Delta(const vector<char> &dna, int dim, SARS_CoV_2 *ancestor) : SARS_CoV_2(dna, dim, DELTA,
                                                                                  ancestor) {

}

void Delta::personalChange() {
    double p = 1 / this->getDim();
    srand( (unsigned)time( NULL ) );
    for (int i = 0 ; i < this->getDim(); i++){
        char ch =  this->getDna()[i];
        if (ch == 'A' || ch == 'C' || ch == 'G'){
            double prob = (double) rand()/RAND_MAX;
            if (prob <= p){
                if(this->getDna()[i] == 'A'){
                    updateDNA(i, 'T');
                    continue;
                }
                if(this->getDna()[i] == 'C'){
                    updateDNA(i, 'G');
                    continue;
                }
                updateDNA(i, 'C');
            }
        }
    }

}

void Delta::printStrain() {
    cout << 'd';
}

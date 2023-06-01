//
// Created by YamEl on 4/19/2022.
//

#include "Omicron.h"
Omicron::Omicron(const vector<char> &dna, int dim, SARS_CoV_2 *ancestor) : SARS_CoV_2(dna, dim, OMICRON,
                                                                                  ancestor) {

}

void Omicron::personalChange() {
    double p = 2 / this->getDim();
    srand( (unsigned)time( NULL ) );
    for (int i = 0 ; i < this->getDim(); i++){
        char ch =  this->getDna()[i];
        if (ch == 'T' || ch == 'C' || ch == 'G'){
            double prob = (double) rand()/RAND_MAX;
            if (prob <= p){
                if(this->getDna()[i] == 'T'){
                    updateDNA(i, 'C');
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

void Omicron::printStrain() {
    cout << 'o';

}

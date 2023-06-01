//
// Created by YamEl on 4/19/2022.
//

#include "Alpha.h"

Alpha::Alpha(const vector<char> &dna, int dim, SARS_CoV_2 *ancestor) : SARS_CoV_2(dna, dim, ALPHA,
                                                                                              ancestor) {

}

void Alpha::personalChange() {
    double p = 0.37;
    srand( (unsigned)time( NULL ) );
    for (int i = 0 ; i < this->getDim(); i++){
        char ch =  this->getDna()[i];
        if (ch == 'T' || ch == 'A'){
            double prob = (double) rand()/RAND_MAX;
            if (prob <= p){
                if(this->getDna()[i] == 'A'){
                    updateDNA(i, 'T');
                    continue;
                }
                updateDNA(i, 'A');
            }
        }
    }

}

void Alpha::printStrain() {
    cout << 'a';
}

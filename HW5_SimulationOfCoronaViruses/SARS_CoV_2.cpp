//
// Created by YamEl on 4/19/2022.
//

#include "SARS_CoV_2.h"

SARS_CoV_2::SARS_CoV_2(const vector<char> &dna, int dim, int strain, SARS_CoV_2 *ancestor) : dna(dna), r_counter(0) ,dim(dim),
                                                                                             strain(strain),
                                                                                             ancestor(ancestor) {
    if (this->ancestor)   (this->ancestor)->incR();

}

SARS_CoV_2::~SARS_CoV_2() {
    if (this->ancestor)   (this->ancestor)->decR();
}

//Getters
const vector<char> &SARS_CoV_2::getDna() const {
    return dna;
}
int SARS_CoV_2::getDim() const {
    return dim;
}
int SARS_CoV_2::getStrain() const {
    return strain;
}
int SARS_CoV_2::getRCounter() const {
    return r_counter;
}
SARS_CoV_2 *SARS_CoV_2::getAncestor() const {
    return ancestor;
}


//Updates

double SARS_CoV_2::getPower() const {
    return power;
}

void SARS_CoV_2::updateDNA(int index, char ch) {
    this->dna[index] = ch;
}

void SARS_CoV_2::updatePower(vector<char> &target) {
    int counter = 0;
    for (int i = 0; i < this->dim; ++i) {
        if (this->dna[i] == target[i])  counter++;
    }
    this->power = counter / this->dim;
}

void SARS_CoV_2::incR() {
    this->r_counter++;
}

void SARS_CoV_2::decR() {
    this->r_counter--;
}

void SARS_CoV_2::setDna(const vector<char> &dna) {
    SARS_CoV_2::dna = dna;
}




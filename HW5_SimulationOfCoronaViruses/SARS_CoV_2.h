//
// Created by YamEl on 4/19/2022.
//

#ifndef HW1_SARS_COV_2_H
#define HW1_SARS_COV_2_H

#include "iostream"
#include "vector"
#include "set"

using namespace std;
enum strains{ALPHA, DELTA, OMICRON};
//set<char> validChars = {'A','T','C','G'};

class SARS_CoV_2 {
private:
    vector<char> dna;
    int dim;
    int strain;
    double power;

    int r_counter;
    SARS_CoV_2* ancestor; //if the virus is ancestor it will be NULL

public:
    //Constructor & Destructor
    SARS_CoV_2(const vector<char> &dna, int dim, int strain, SARS_CoV_2 *ancestor = NULL);
    virtual ~SARS_CoV_2();


    //Getters
    const vector<char> &getDna() const;
    int getDim() const;
    int getStrain() const;
    int getRCounter() const;
    SARS_CoV_2 *getAncestor() const;
    double getPower() const;

    //Setters
    void setDna(const vector<char> &dna);

    //Updates
    void updateDNA(int index, char ch);
    virtual void personalChange() = 0;
    void updatePower(vector<char> &target);
    void incR();
    void decR();

    //Prints
    virtual void printStrain() = 0;

};



#endif //HW1_SARS_COV_2_H

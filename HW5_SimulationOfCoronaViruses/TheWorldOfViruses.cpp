//
// Created by YamEl on 4/19/2022.
//

#include <algorithm>
#include "TheWorldOfViruses.h"



int TheWorldOfViruses::getDim() const {
    return dim;
}

int TheWorldOfViruses::getGen() const {
    return gen;
}

int TheWorldOfViruses::getMaxGen() const {
    return max_gen;
}

TheWorldOfViruses::TheWorldOfViruses(int dim, int maxGen, const vector<SARS_CoV_2 *> &ancestors,
                                     const vector<char> &target) : dim(dim), max_gen(maxGen), ancestors(ancestors),
                                                                   target(target) {
    for (int i = 0; i < ancestors.size(); ++i) {
        int strain = ancestors[i]->getStrain();
        switch (strain) {
            case ALPHA:
                viruses.push_back(new Alpha(ancestors[i]->getDna(), this->dim, ancestors[i]));
                break;
            case DELTA:
                viruses.push_back(new Delta(ancestors[i]->getDna(), this->dim, ancestors[i]));
                break;
            case OMICRON:
                viruses.push_back(new Omicron(ancestors[i]->getDna(), this->dim, ancestors[i]));
                break;
        }

    }
}

void TheWorldOfViruses::updatePowers() {
    for (int i = 0; i < viruses.size(); ++i) {
        viruses[i]->updatePower(this->target);
    }
}

void TheWorldOfViruses::personal_change_to_all() {
    for (int i = 0; i < viruses.size(); ++i) {
        viruses[i]->personalChange();
    }

}

void TheWorldOfViruses::groupChange() {
    sort(viruses.begin(),
         viruses.end(),
         [](SARS_CoV_2* x, SARS_CoV_2* y) { return ((x->getPower()) < (y->getPower()));});

    delete viruses[viruses.size()-1];
    viruses.pop_back();
    delete viruses[viruses.size()-1];
    viruses.pop_back();

    int i, j, s,t;
    srand( (unsigned)time(NULL) );
    i = rand() % this->ancestors.size();
    j = rand() % this->ancestors.size();
    while(i==j){ // case i==j
        j = rand() % this->ancestors.size();
    }
    s = (rand() % (this->dim-4))+2;
    t = (rand() % (this->dim-4))+3;
    while (!(s<t)){
        t = (rand() % (this->dim-4))+3;
    }

    vector<char> son1, son2, dad1 = ancestors[i]->getDna(), dad2 = ancestors[j]->getDna();

    for (int k = 0; k < this->dim; ++k) {
        if (k>s && k<=t){
            son1.push_back(dad2[k]);
            son2.push_back(dad1[k]);
            continue;
        }
        son1.push_back(dad1[k]);
        son2.push_back(dad2[k]);
    }

    switch (ancestors[i]->getStrain()) {
        case ALPHA:
            viruses.push_back(new Alpha(son1, this->dim, ancestors[i]));
            break;
        case DELTA:
            viruses.push_back(new Delta(son1, this->dim, ancestors[i]));
            break;
        case OMICRON:
            viruses.push_back(new Omicron(son1, this->dim, ancestors[i]));
            break;
    }

    switch (ancestors[j]->getStrain()) {
        case ALPHA:
            viruses.push_back(new Alpha(son2, this->dim, ancestors[j]));
            break;
        case DELTA:
            viruses.push_back(new Delta(son2, this->dim, ancestors[j]));
            break;
        case OMICRON:
            viruses.push_back(new Omicron(son2, this->dim, ancestors[j]));
            break;
    }



}

bool TheWorldOfViruses::sim_gen() {
    if (gen >= max_gen) return false;
    personal_change_to_all();
    updatePowers();
    groupChange();
    updatePowers();
    gen++;
    return true;
}

void TheWorldOfViruses::sim_to_end() {
    if (is_one())   return;
    while (sim_gen()){
        if (is_one())   return;
    }
    updatePowers();
    sort(viruses.begin(),
         viruses.end(),
         [](SARS_CoV_2* x, SARS_CoV_2* y) { return ((x->getPower()) < (y->getPower()));});

}



bool TheWorldOfViruses::is_one() {
    for (int i = 0; i < viruses.size(); ++i) {
        if (viruses[i]->getPower() == 1)
            return true;
    }
    return false;
}

void TheWorldOfViruses::print() {
    for (int i = 0; i < viruses.size() ; ++i) {
        viruses[i]->printStrain();
        cout << ' ';
        vector<char> dna = viruses[i]->getDna();
        for (int j = 0; j < this->dim; ++j) {
            cout << dna[j];
            if (j != (this->dim)-1) cout << ' ';
        }
        cout << endl;
    }

    cout << endl;

    for (int i = 0; i < ancestors.size() ; ++i) {
        ancestors[i]->printStrain();
        cout << ' ';
        vector<char> dna = ancestors[i]->getDna();
        for (int j = 0; j < this->dim; ++j) {
            cout << dna[j];
            if (j != (this->dim)-1) cout << ' ';
        }
        cout << " " << ancestors[i]->getRCounter() << endl;
    }

    cout << endl;

    viruses[0]->printStrain();
    cout << ' ';
    vector<char> dna = viruses[0]->getDna();
    for (int j = 0; j < this->dim; ++j) {
        cout << dna[j];
        if (j != (this->dim)-1) cout << ' ';
    }
    cout << endl;



}




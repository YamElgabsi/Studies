//
// Created by YamEl on 4/19/2022.
//

#include <fstream>
#include <algorithm>
#include "Simulator.h"

bool is_number(const string& s){
    return !s.empty() && find_if(s.begin(),
                                      s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end();
}

void raise_error(){
    cerr << "ERROR: Invalid input.";
    exit(1);
}

bool read_config_file(vector<string>& config_data, int& dim, vector<char>& target, int& max_gen){

    if (config_data.size() != 3) return false;

    if (!is_number(config_data[0])) return false;
    dim = stoi(config_data[0]);
    if (dim < 3 || dim > 1000) return false;

    int base_counter = 0;
    for (int i = 0; i < config_data[1].size(); ++i) {
        char ch = (config_data[1][i]);
        if (i == 0 || i%2 == 0){//need to be a base gen char
            if (++base_counter > dim) return false;
            if(!isBase(ch)) return false;
            target.push_back(ch);
            continue;
        }
        if (ch != ' ')  return false;
    }

    if (!is_number(config_data[2])) return false;
    max_gen = stoi(config_data[2]);
    if (max_gen<0 || max_gen > 10000000 ) return false;

    return true;
}

bool read_first_generation_file(vector<string>& first_generation_data, vector<SARS_CoV_2 *> &ancestors, int& dim, int& num_of_viruses){

    if (!is_number(first_generation_data[0])) return false;
    num_of_viruses = stoi(first_generation_data[0]);
    if (num_of_viruses < 3 || num_of_viruses >= 200) return false;

    if (first_generation_data.size() != num_of_viruses+1) return false;
    
    for (int i = 1; i <= num_of_viruses; ++i) {
        int base_counter = 0;
        char strain;
        vector<char> dna;
        for (int j = 0; j < first_generation_data[i].size(); ++j) {
            char ch = first_generation_data[i][j];
            
            if (j == 0) {
                if (!isCorona(ch))  return false;
                strain = ch;
                continue;
            }

            if (j%2 == 0){
                if(!isBase(ch)) return false;
                if(++base_counter > dim) return false;
                
                dna.push_back(ch);
                if(base_counter == dim){
                    switch (strain) {
                        case 'a':
                            ancestors.push_back(new Alpha(dna, dim));
                            break;
                        case 'd':
                            ancestors.push_back(new Delta(dna, dim));
                            break;
                        case 'o':
                            ancestors.push_back(new Omicron(dna, dim));
                            break;
                    }
                }
                continue;
            }
            if (ch != ' ') return false;
        }
    }

    return true;
}



int run(int argc, char **argv) {
    if( argc != 3)  raise_error();

    ifstream config(argv[1]);
    if (!config) raise_error();

    ifstream first_generation(argv[2]);
    if (!first_generation)  raise_error();

    string str;
    vector<string> config_data;
    vector<string> first_generation_data;

    //read file to vector of string
    while (getline(config,str)) {
        if(str.substr(str.size()-2).compare("/r")){//handling /r reading in Windows file
            str.erase(str.size() - 1);
        }
        config_data.push_back(str);
    }
    while (getline(first_generation,str)) {
        if(str.substr(str.size()-2).compare("/r")){//handling /r reading in Windows file
            str.erase(str.size() - 1);
        }
        first_generation_data.push_back(str);
    }

    int dim, max_gen;
    vector<char> target;
    if(!read_config_file(config_data, dim, target,max_gen)) raise_error();

    int num_of_viruses;
    vector<SARS_CoV_2 *> ancestors;
    if(!read_first_generation_file(first_generation_data, ancestors, dim, num_of_viruses)) raise_error();

    TheWorldOfViruses worldOfViruses = TheWorldOfViruses(dim,max_gen,ancestors,target);
    worldOfViruses.sim_to_end();
    worldOfViruses.print();





    return 0;
}

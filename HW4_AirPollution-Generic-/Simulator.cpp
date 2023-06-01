//
// Created by YamEl on 12/17/2021.
//

#include "Simulator.h"

void error(string output) {
    cerr << output;// << endl;
    exit(1);
}

void char2int(char& ch, int& intR){
    stringstream data;
    data << ch;
    data >> intR;
}
void removeTypeFromString(string& str){
    stringstream newString;
    for(unsigned int i = 1; i < str.length(); i++)
        newString << str[i];
    newString >> str;
}

void string2int(string& str, int& intR){
    stringstream data;
    data << str;
    data >> intR;
}

void string2double(string& string, double& doubleR){
    stringstream data;
    data << string;
    data >> doubleR;
}

void simMetropolisFromFile(int argc, char* argv[]){
    //READING FILES
    if (argc != 3) error("Wrong number of arguments");
    ifstream met_graph(argv[1]);
    if (!met_graph) error();
    ifstream vehicle_locations(argv[2]);
    if (!vehicle_locations) error();

    int size, row = 0, col = 0, counter = 0,counterCARS = 0;
    char ch, type;
    string temp, carName;
    double** matrix;
    string cars[max_cars];
    Map<string,int> locations;

    met_graph.get(ch);
    char2int(ch, size);
    if(size <= 0) error();

    met_graph.get(ch);
    if (ch != '\n') error();//need to be end of a line

    matrix = new double*[size];
    for (int i = 0; i < size; ++i)
        matrix[i] = new double[size];

    while (met_graph.get(ch)){
        if(counter % size == 0 && col != 0) {//need to be end of line
            if (ch != '\n') error();
            row++;
            col = 0;
            temp = "";
            continue;
        }

        if(ch != ' ' && ch != '\n'){//if ch is a part of a number
            temp += ch;
            continue;
        }

        if (ch == ' ' || ch == '\n'){ // reading number completed
            counter++;
            string2double(temp,matrix[row][col++]);
            temp = "";
            if (ch == '\n'){
                if (col > size) //it is not good!
                    error();
                col = 0;
                row++;
            }

            continue;
        }
    }
    counter = 0;
    temp = "";

    int junction, carId;
    while (vehicle_locations.get(ch)){
        if (counter == 0){
            char2int(ch,junction);
            if (junction > size) error();
            counter++;
            continue;
        }
        if (counter == 1){
            if (ch != ':')  error();
            counter++;
            continue;
        }
        if(ch == ' '){ // car id reading is complete, or we start reading car id
            if (counter == 2) {// we start read ids;
                counter++;
                continue;
            }
            // car reading is completed
            carName = temp;
            cars[counterCARS] = carName;
            locations.insert(carName,junction);
            counterCARS++;
            counter++;
            temp = "";
            continue;
        }

        if (ch == '\n'){
            if (temp.compare("") != 0){
                // number reading is completed
                //string2int(temp,carId);
                carName = temp;
                cars[counterCARS] = carName;
                locations.insert(carName,junction);
                counterCARS++;
                counter++;
                temp = "";
            }
            counter = 0;
            continue;
        }

        //if it is a number
        temp+= ch;
        counter++;

    }
    Metropolis oranjestad = Metropolis(matrix, size);

    for (int i = 0; i < counterCARS; ++i) {
        for (int j = 0; j < counterCARS; ++j) {
            temp = cars[j];
            type = temp[0];
            removeTypeFromString(temp);
            string2int(temp,carId);
            if (carId == (i+1)){
                junction = *locations[cars[j]];
                switch (type) {
                    case 'F': {
                        oranjestad.setNewCar(junction, FAMILY);
                        break;
                    }
                    case 'S':{
                        oranjestad.setNewCar(junction, SPORTS);
                        break;
                    }
                    case 'L':{
                        oranjestad.setNewCar(junction, LUXURY);
                        break;
                    }
                    case 'M':
                        oranjestad.setNewCar(junction, MASERATI);
                        break;
                }
                break;
            }
        }

    }

    int times;
    string input;
    //cout << "ENTER TIMES:" << endl;
    getline(cin, input);
    string2int(input,times);
    oranjestad.moveALL(times);
    //cout << endl << "AIR:" << endl;
    oranjestad.printRoadsAir();
    //cout << endl << "JUNCTIONS:" << endl;
    oranjestad.printJunctions();
}


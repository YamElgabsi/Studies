#include "Simulator.h"

using namespace std;

int bla() {

    int size = 6;

    double** matrix;
    matrix = new double*[size];
    for (int i = 0; i < size; ++i)
    {
        matrix[i] = new double[size];

    }
    for(int x=0;x<size;x++)
    {
        for(int y=0;y<size;y++)
        {
            if (x == y)
                matrix[x][y] = 0.0;
            else
                matrix[x][y] = 1.3;
        }
    }


    Metropolis metropolis = Metropolis(matrix, size);
    cout << "1.Roads LEN:" << endl; metropolis.printRoads();

    metropolis.setNewCar(3,FAMILY);
    metropolis.setNewCar(1, LUXURY);
    metropolis.setNewCar(2,FAMILY);
    metropolis.setNewCar(1,FAMILY);
    metropolis.setNewCar(3,SPORTS);
    metropolis.setNewCar(1,MASERATI);
    cout << "2.JUN: BEFORE: " << endl;metropolis.printJunctions();cout << endl;
    metropolis.moveALL(20);
    cout << "3.JUN:  AFTER:" << endl;
    metropolis.printJunctions();cout << endl;
    cout << "4.Roads AIR:" << endl; metropolis.printRoadsAir();



    return 0;
}


int main(int argc, char* argv[]){
    simMetropolisFromFile(argc,argv);
    return 0;
}

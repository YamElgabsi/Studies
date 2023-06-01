#include <iostream>
#include "Board.h"

int main(int argc, char *argv[])
{
    int referees, players;
    if(argc != 3){
        cerr<<"ERROR: USAGE <executable> NUM_REFEREES MAX_ATHLETES"<<endl;
        return 1;
    }
    stringstream data1(argv[1]);
    stringstream data2(argv[2]);
    data1 >> referees;
    data2 >> players;


    //start game!
    string choice;
    Board board(players,referees);
    while (true){
        //cout<<"Enter Your Choice"<< endl;
        getline(cin, choice);
        if (choice == "0")
            break;
        if (choice == "1")
            board.setPlayer();
        if( choice == "2")
            board.printPlayerGrades();

        if( choice == "3")
            board.printPlayerMean();

        if( choice == "4")
            board.printScoreSummary();

        if (choice == "5")
            board.printMeanVector();

        if (choice == "6")
            board.printCovarianceMatrix();

        if (choice != "0" && choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6")
            cerr<<"ERROR: invalid command; type 0 for exit"<<endl;
    }

    return 0;
}

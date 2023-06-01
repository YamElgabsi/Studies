//
// Created by YamEl on 11/26/2021.
//

#ifndef HW02_BOARD_H
#define HW02_BOARD_H

#include "Hex.h"

const int size = 11;
inline bool isLegalIndex(int row, int col){
    if (row < 0 || col < 0 || row>=size || col >=size)
        return false;
    return true;
}
inline int toInt(char c){
    if ((c > 75) || (c<65)) //if the char not between A to K
        return -1;
    return int(c-'@');
}

//GLOBAL FUNCTIONS
bool get_valid_input(string &input, bool &quit);
void update_by_input(string input, int &row, int &col);
void selects_turn(int turn, int &player);

class Board {
private:
    Hex** board;

public:
    //constructor & Destructors
    Board();
    ~Board();




    bool makeMove(int player, int row, int col);

    bool canReachRight(int i , int j);
    bool canReachUp(int i , int j);

    void turnAllFalse();

    bool isWon(int player);
    bool isWon_BLUE();
    bool isWon_RED();
    void print();

};


#endif //HW02_BOARD_H

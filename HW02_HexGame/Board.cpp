//
// Created by YamEl on 11/26/2021.
//
#include <sstream>
#include "Board.h"

//global function
bool get_valid_input(string &input, bool &quit){
    getline(cin, input);
    if (input == "QUIT"){
        quit = true;
        return true;
    }
    if (input.length()!=2 && input.length()!=3 ){
        cerr << "Invalid move; the game awaits a valid move." << endl;
        return false;
    }
    if (input[0] < 65 || input[0] > 75 ){
        cerr << "Invalid move; the game awaits a valid move." << endl;
        return false;
    }
    if (input.length() == 2){
        if (input[1] < 49 || input[1] > 57) {
            cerr << "Invalid move; the game awaits a valid move." << endl;
            return false;
        }
        return true;
    }

    if (input.length() == 3){
        if (input[1] != '1' || input[2] > 49 || input[2] < 48){
            cerr << "Invalid move; the game awaits a valid move." << endl;
            return false;
        }
        return true;
    }
    return false;
}
void update_by_input(string input, int &row, int &col){
    stringstream temp;
    col = toInt(input[0]);
    if(input.length() == 2)
        temp << input[1] - '0';
    else
        temp << input.substr(1,2);
    temp >> row;
}
void selects_turn(int turn, int &player){
    if (turn%2 == 0){
        player = RED;
        cout << "R:" << endl;
    }
    else{
        player = BLUE;
        cout << "B:" << endl;
    }
}




//constructor & Destructors
Board::Board() {
    board = new Hex*[size];
    for(int i = 0; i < size; i++){
        board[i] = new Hex[size];
    }
}
Board::~Board() {
    for(int i = 0; i < size; i++){
        delete[] board[i];
    }
    delete[]board;

}



bool Board::makeMove(int player, int row, int col) {
    if (!board[row][col].isEmpty()){
        cerr << "Invalid move; the game awaits a valid move." << endl;
        return false;
    }

    if (player == BLUE){
        board[row][col].setColorBlue();
        return true;
    }
    if (player == RED){
        board[row][col].setColorRed();
        return true;
    }
    cerr << "Invalid move; wrong player!" << endl;
    return false;
}

void Board::turnAllFalse() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j].turnFalse();
        }
    }
}

bool Board::isWon(int player) {
    if (player == BLUE)
        return isWon_BLUE();
    return isWon_RED();
}
bool Board::canReachRight(int i , int j){
    if ( isLegalIndex(i,j) ){
        if (board[i][j].isBlue() && !board[i][j].isVisited()){
            board[i][j].turnTrue();
            if( j == size-1)
                return true;
            if(
            canReachRight(i-1,j)      ||
            canReachRight(i-1,j+1) ||
            canReachRight(i,j-1)      ||
            canReachRight(i,j+1)      ||
            canReachRight(i+1,j-1) ||
            canReachRight(i+1,j))
                return true;
        }

    }
    return false;
}
bool Board::canReachUp(int i , int j){
    if ( isLegalIndex(i,j) ){
        if (board[i][j].isBlue() && !board[i][j].isVisited()){
            board[i][j].turnTrue();
            if( i == size-1)
                return true;
            if(
            canReachUp(i-1,j)||
            canReachUp(i-1,j+1)||
            canReachUp(i,j-1)||
            canReachUp(i,j+1)||
            canReachUp(i+1,j-1)||
            canReachUp(i+1,j))
                return true;
        }

    }
    return false;
}
bool Board::isWon_BLUE() {
    for (int i = 0; i < size; ++i) {
        turnAllFalse();
        if(canReachRight(i,0) )
            return true;
    }
    return false;
}
bool Board::isWon_RED() {
    turnAllFalse();
    for (int j = 0; j < size; ++j) {
        if( canReachUp(0,j) )
            return true;
    }
    return false;
}

void Board::print() {
    for (int i = 0; i < size; i++) {
        for (int space = 0; space < i; space++)
            cout << ' ';
        for (int j = 0; j < size; j++){
            if (j == size-1)
                cout << board[i][j].toChar();
            else
                cout << board[i][j].toChar() << " " ;
        }
        cout<<endl;
    }

}




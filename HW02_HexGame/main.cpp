#include "Board.h"


int main() {
    string input;
    int player, turn = 1, row, col;
    bool  quit = false;
    Board *board = new Board;
    while (true){
        board->print();
        selects_turn(turn,player);
        while (!get_valid_input(input,quit)); //get input until pass valid tests
        if (quit){
            if (player == BLUE){
                cout << "B: QUIT" << endl;
                board->print();
                cout << "R wins the game." << endl;
            }
            else{
                cout << "R: QUIT" << endl;
                board->print();
                cout << "B wins the game." << endl;
                break;
            }
        }
        update_by_input(input,row,col);
        if (board->makeMove(player,row-1,col-1))
            turn++;
        if (board->isWon(player)){
            if (player == BLUE){
                cout << "B wins the game." << endl;
                break;
            }
            cout << "R wins the game." << endl;
            break;
        }
    }
    delete board;
}

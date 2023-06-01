//
// Created by YamEl on 11/10/2021.
//

#ifndef HW01_BOARD_H
#define HW01_BOARD_H
#include "string"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <iomanip>

using namespace std;
const int max_size = 10000;
const int max_name_len = 18;
inline int precision(float x){
    int x_int(x);
    if (x - x_int == 0.0)
        return 0;
    return 2;
}

class Board {
public:
    //c'tor & d'tor
    Board(int &number_players, int &number_referees);
    ~Board();

    //getters
    int getNumberOfPlayers();
    int getNumberOfReferees();
    int getPlayersCounter();

    // function
    void setPlayerName(int &index, string name);
    string getPlayerName(int &index);
    void setPlayerGrade(int player_index, int referee_index, float grade);
    float getPlayerGrade(int player_index, int referee_index);
    int getPlayerIndex(string name);
    bool setPlayerGrades(string grades, int playerIndex);
    float getPlayerMean(int player_index);
    float getRefereeExpectedValue(int referee_index);
    //main function
    bool setPlayer();
    void printPlayerGrades();
    void printPlayerMean();
    void printScoreSummary();
    void printMeanVector();
    void printCovarianceMatrix();
private:

    int numberOfPlayers;
    int numberOfReferees;
    float** board;
    string ** players;
    int players_counter;

};

//global functions
bool is_a_number(string str);
void remove_after_dots(string &str);

#endif //HW01_BOARD_H

//
// Created by YamEl on 11/10/2021.
//

#include "Board.h"
//global functions
bool is_a_number(string str){
    int len = str.length();
    for (int i; i < len; i++){
        if(!isdigit(str[i]))
            return false;
    }
    return true;
}

void remove_after_dots(string &str) {
    str.erase(str.find_last_not_of('0') + 1, string::npos );
    if(str.find('.') == str.length()-1)
    {
        str.erase (str.find_last_not_of('.') + 1, string::npos );
    }
}

//c'tor & d'tor
Board::Board(int &number_players, int &number_referees) {
    numberOfPlayers = number_players;
    numberOfReferees = number_referees;
    players = new string *[number_players];
    for(int i = 0; i < number_players; i++ ){
        players[i] = new string("NoName");
    }

    board = new float *[number_players];
    for(int i = 0 ; i < number_players; i++){
        board[i] = new float [number_referees];
    }
    players_counter = 0;
}
Board::~Board() {
    for (int i = 0; i < getNumberOfPlayers(); i++){
        delete[]board[i];
    }
    delete []board;
    delete []players;
}

//getters
int Board::getNumberOfPlayers()  {
    return numberOfPlayers;
}
int Board::getNumberOfReferees()  {
    return numberOfReferees;
}
int Board::getPlayersCounter() {
    return players_counter;
}

// function
void Board::setPlayerName(int &index, string name) {
    delete(players[index]);
    players[index] = new string(name);
}
string Board::getPlayerName(int &index){
    return *players[index];
}
void Board::setPlayerGrade(int player_index, int referee_index, float grade) {
    board[player_index][referee_index] = grade;
}
float Board::getPlayerGrade(int player_index, int referee_index) {
    float grade(board[player_index][referee_index]);
    return grade;
}
int Board::getPlayerIndex(string name) {
    for (int i = 0; i < numberOfPlayers; ++i) {
        if (name == getPlayerName(i))
            return i;
    }
    return -1;
}
bool Board::setPlayerGrades(string grades, int playerIndex) {
    int len = grades.length();
    string strings[len];
    char c;
    int currIndex = 0;
    int startIndex = 0, endIndex;
    string sub_string = "";
    int grades_counter = 0;
    for (int i = 0; i <= len; i++){
        c = grades[i];
        if (c == ',' || c == ' ' || i == len)
        {
            grades_counter++;
            endIndex = i;
            sub_string = "";
            sub_string.append(grades, startIndex, endIndex - startIndex);
            strings[currIndex] = sub_string;
            currIndex += 1;
            startIndex = endIndex + 1;
        }
    }

    int not_valid_grades_counter = 0;
    for(int i = 0; i < grades_counter; i++){
        if (!is_a_number(strings[i]))
            not_valid_grades_counter++;
    }

    if (not_valid_grades_counter != 0 || grades_counter != numberOfReferees){
        cerr<<"ERROR: invalid input"<<endl;
        return false;
    }

    float grade;
    for(int i = 0; i < grades_counter; i++){
        stringstream data(strings[i]);
        data >> grade;
        setPlayerGrade(playerIndex, i, grade);
    }
    players_counter++;
    return true;
}
float Board::getPlayerMean(int player_index) {
    float sum = 0.0;
    float referees(numberOfReferees);
    for(int i = 0; i < numberOfReferees; i++){
        sum += getPlayerGrade(player_index,i);
    }
    return (sum/referees);
}
float Board::getRefereeExpectedValue(int referee_index) {
    float m(players_counter);
    float sigma = 0.0;
    for(int i = 0; i < numberOfPlayers; i++){
        if(*players[i] != "NoName"){
            sigma += getPlayerGrade(i,referee_index);
        }
    }
    return  (1.0 / m * sigma);

}

//main function
bool Board::setPlayer() {
    string grades, name;
    int player_index;
    bool isInTheSystem = true; // will be false if the player is not already in the system
    if (players_counter == numberOfPlayers){
        cout<<"ERROR: MAX_ATHLETES exceeded"<<endl;
        return false;
    }
    //cout<<"Please Enter Player Name:"<<endl;
    getline(cin,name);

    if (name.length() >= max_name_len){
        cerr<<"ERROR: invalid input"<<endl;
        return false;
    }
    player_index = getPlayerIndex(name);
    if (player_index == -1){ // in case that the player not in the system
        player_index = players_counter;
        isInTheSystem = false;
    }

    //cout<<"Please Enter The Player Grades:"<<endl;
    getline(cin,grades);

    if (!setPlayerGrades(grades, player_index))
        return false;

    if (isInTheSystem){
        players_counter--;
    } else{
        setPlayerName(player_index,name);
    }
    return true;

} //number 1
void Board::printPlayerGrades() {
    string name;
    int player_index;

    cout<<"Please Enter Player Name:"<<endl;
    getline(cin,name);

    player_index = getPlayerIndex(name);
    if (player_index == -1){
        cerr<<"ERROR: "<<name<<" does not exist"<<endl;
        return;
    }
    int grade = getPlayerGrade(player_index,0);
    cout<<name<<"=["<<grade;
    for(int i = 1; i < numberOfReferees; i++){
        grade = getPlayerGrade(player_index,i);
        cout<<","<<grade;
    }
    cout<<"]"<<endl;

} //number 2
void Board::printPlayerMean() {
    string name;
    int player_index;
    float mean;

    cout<<"Please Enter Player Name:"<<endl;
    getline(cin,name);

    player_index = getPlayerIndex(name);
    if (player_index == -1){
        cerr<<"ERROR: "<<name<<" does not exist"<<endl;
        return;
    }
    mean = getPlayerMean(player_index);
    cout<<name<<", "<<fixed<<setprecision(precision(mean))<<mean<<endl;
} //number 3
void Board::printScoreSummary(){
    float mean;
    string name;
    if (players_counter == 0){
        cerr<<"ERROR: no records in the system"<<endl;
        return;
    }
    for (int i = 0; i < numberOfPlayers; ++i) {
        if (*players[i] != "NoName"){
            mean = getPlayerMean(i);
            name = getPlayerName(i) ;
            cout<<name<<", "<<fixed<<setprecision(precision(mean))<<mean<<endl;
        }
    }
} //number 4
void Board::printMeanVector() {
    float m = players_counter, v;
    if (m == 0.0){
        cerr<<"ERROR: no records in the system"<<endl;
        return;
    }
    stringstream data;
    string str;
    v = getRefereeExpectedValue(0);
    cout<<"mean=[";
    data<<fixed<<setprecision(precision(v))<<v;
    data >> str;
    remove_after_dots(str);
    cout<<str;

    for(int j = 1; j < numberOfReferees; j++){
        stringstream data;
        string str;
        v = getRefereeExpectedValue(j);
        data<<fixed<<setprecision(precision(v))<<v;
        data >> str;
        remove_after_dots(str);
        cout<<","<<str;
    }
    cout<<"]"<<endl;
} //number 5
void Board::printCovarianceMatrix() {
    float c, toNorm;
    float m(players_counter);
    float sigma, sub1, sub2, mul;
    stringstream data;
    string str;
    if (m == 0.0){
        cerr<<"ERROR: no records in the system"<<endl;
        return;
    }

    if (numberOfReferees == 1)
        toNorm = 1.0/m;
    else
        toNorm = 1.0/(m - 1.0);
    cout<<"cov=["<<endl;

    for(int i = 0; i < numberOfReferees; i++){
        for(int j = 0; j < numberOfReferees; j++){
            sigma = 0.0;
            for(int k = 0; k < players_counter; k++) {
                sub1 = getPlayerGrade(k,i)- getRefereeExpectedValue(i);
                sub2 = getPlayerGrade(k,j)- getRefereeExpectedValue(j);
                mul = sub1*sub2;

                sigma+= mul;
            }
            c = toNorm*sigma;
            stringstream data;
            string str;
            data<<fixed<<setprecision(precision(c))<<c;
            data >> str;
            remove_after_dots(str);
            if (j==0)
                cout<<str;
            else
                cout<<","<<str;
        }
        cout<<endl;
    }
    cout<<"]"<<endl;
} //number 6










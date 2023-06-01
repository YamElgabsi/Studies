//
// Created by Yam Elgabsi on 11/06/2022.
//

#include "View.h"
#include "Model.h"
#include "vector"
#include <iostream>
#include <sstream>
#include "map"
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

enum command{cmdCourse = 0, cmdPosition, cmdDestination, cmdAttack, cmdStop, cmdDefault, cmdSize, cmdZoom, cmdPan, cmdShow, cmdStatus, cmdCreate, cmdGo};
int inline command_to_enum(const string& str);
void myExit(const string& str);

class Controller {
private:
    Model &model;
    view_ptr view;
    vector<string> files;

public:
    Controller(int argc, char **argv);
    bool get_command_from_user();
    void Play();

protected:
    void check_warehouse();
    void check_trucks();
    bool parse_command(string &command);
    void do_vehicle_command(stringstream &ss, string &name);
    void do_rest_command(stringstream& ss, string &cmd);
    int get_truck_index_files();
    static double getTime(string &start, string &end, string &leave);
    static void parseLine(string &line, string &nextStop, string &arriveTime, int &crates, string &leaveTime);
    void parseFirstLine(string &line, int idx, string &truckName, string &startingPoint, ifstream &truckFile);
};
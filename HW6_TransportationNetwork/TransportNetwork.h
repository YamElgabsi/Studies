//
// Created by YamEl on 5/20/2022.
//

#ifndef HW02_TRANSPORTNETWORK_H
#define HW02_TRANSPORTNETWORK_H

#include "IntercityStation.h"
#include "CentraalStation.h"
#include "StadStation.h"
#include "Graph.h"
#include <sstream>
#include <cstring>
#include <fstream>
#include <algorithm>

class TransportNetwork {
private:
    vector<unique_ptr<Station>> stations;
    map<int,Graph> network;

    map<int,int> transits;
    map<int,int> stop_times;

    map<int,int> dockID_to_stationID;
    map<int,string> stationID_to_name;

    #define dockID_to_stationNAME(id) stationID_to_name[dockID_to_stationID[id]]

    int numOfStation;
    ofstream out;

public:
    //--The Big Five--
    TransportNetwork(string fileName = "output.dat");
    ~TransportNetwork();
    TransportNetwork(const TransportNetwork& other) = delete;
    TransportNetwork& operator=(const TransportNetwork& other) = delete;
    TransportNetwork(const TransportNetwork&& other) = delete;

    //--Setters--
    // work only if the network is empty
    void setStopTime(int type, int newST);
    void setTransit(int type, int newT);

    //--Manage Functions--
    void addStation(int type, string name);
    void addLine(int type, string from, string to, int weight);

    //--functions--
    void load(string filename);
    void inbound(string name) ;
    void outbound(string name) ;
    void print();
    void uniExpress(string source, string target);
    void multiExpress(string source, string target);


protected:
    void inbound_helper(string name, int& res_counter, stringstream& buf) ;
    void outbound_helper(string name, int& res_counter, stringstream& buf);
    int getStationID(string name); // -1 if name is not in the graph
    int name_station_to_type(string name);
    int name_dock_to_type(string name); // -1 if the name invalid
};


#endif //HW02_TRANSPORTNETWORK_H

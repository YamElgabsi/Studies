//
// Created by YamEl on 5/20/2022.
//

#include "TransportNetwork.h"

TransportNetwork::TransportNetwork(string fileName){
    out.open(fileName);
    network[BUS];    network[TRAM];    network[SPRINTER];    network[RAIL];    network[ALL];
    transits[INTERCITY] = 15; transits[CENTRAAL] = 10; transits[STAD] = 5;
    stop_times[BUS] = 1; stop_times[TRAM] = 2; stop_times[SPRINTER] = 3; stop_times[RAIL] = 5;
    numOfStation = 0;
}

void TransportNetwork::addStation(int type, string name){
    if (type != INTERCITY && type != CENTRAAL && type != STAD)  throw invalid_argument("The type of the station that you want to add must be from the enum");
    for(auto iter = stations.begin(); iter != stations.end(); ++iter){
        if ((*iter)->get_name().compare(name) == 0)
            throw invalid_argument("The name of the new station already taken \n");
    }

    switch (type) {
        case INTERCITY:
            stations.push_back(unique_ptr<Station>(new IntercityStation(name)));
            break;
        case CENTRAAL:
            stations.push_back(unique_ptr<Station>(new CentraalStation(name)));
            break;
        case STAD:
            stations.push_back(unique_ptr<Station>(new StadStation(name)));
            break;
    }


    auto& station = stations[stations.size()-1];

    //update the map dockID_to_stationID
    dockID_to_stationID[station->getBusDockID()] = station->getId();
    dockID_to_stationID[station->getRailDockID()] = station->getId();
    dockID_to_stationID[station->getSprinterDockID()] = station->getId();
    dockID_to_stationID[station->getTramDockID()] = station->getId();

    for(auto graph = network.begin(); graph != network.end(); ++graph){
        switch (graph->first) {
            case BUS:
                graph->second.addVertex(station->getBusDockID());
                break;
            case TRAM:
                graph->second.addVertex(station->getTramDockID());
                break;
            case SPRINTER:
                graph->second.addVertex(station->getSprinterDockID());
                break;
            case RAIL:
                graph->second.addVertex(station->getRailDockID());
                break;
            case ALL:
                graph->second.addVertex(station->getBusDockID());
                graph->second.addVertex(station->getTramDockID());
                graph->second.addVertex(station->getSprinterDockID());
                graph->second.addVertex(station->getRailDockID());
                graph->second.addEdge(station->getBusDockID(),station->getTramDockID(),transits[type], true);
                graph->second.addEdge(station->getBusDockID(),station->getRailDockID(),transits[type], true);
                graph->second.addEdge(station->getBusDockID(),station->getSprinterDockID(),transits[type], true);
                graph->second.addEdge(station->getTramDockID(),station->getSprinterDockID(),transits[type], true);
                graph->second.addEdge(station->getTramDockID(),station->getRailDockID(),transits[type], true);
                graph->second.addEdge(station->getRailDockID(),station->getSprinterDockID(),transits[type], true);
                break;
        }
    }
    numOfStation++;
    stationID_to_name[station->getId()] = name;
}

void TransportNetwork::addLine(int type, string from, string to, int weight){
    if (type != BUS && type != TRAM && type != SPRINTER && type != RAIL)    throw invalid_argument("The type of the line that you want to add must be from the enum");
    if (weight < 1) throw invalid_argument("the time must be longer then 1");
    bool found1 = false, found2 = false;
    int f,t;
    for(auto station = stations.begin(); station != stations.end(); ++station){
        if (found1 && found2) break;
        string name =(*station)->get_name();
        if ((*station)->get_name().compare(from) == 0){
            found1 = true;
            switch (type) {
                case BUS:
                    f = (*station)->getBusDockID();
                    break;
                case TRAM:
                    f = (*station)->getTramDockID();
                    break;
                case SPRINTER:
                    f = (*station)->getSprinterDockID();
                    break;
                case RAIL:
                    f = (*station)->getRailDockID();
                    break;
            }
            continue;
        }
        if ((*station)->get_name().compare(to) == 0){
            found2 = true;
            switch (type) {
                case BUS:
                    t = (*station)->getBusDockID();
                    break;
                case TRAM:
                    t = (*station)->getTramDockID();
                    break;
                case SPRINTER:
                    t = (*station)->getSprinterDockID();
                    break;
                case RAIL:
                    t = (*station)->getRailDockID();
                    break;
            }
            continue;
        }
    }
    if (!(found1 && found2))    throw invalid_argument("Can not add line cecuse one of the station not in the network");

    network[type].addEdge(f,t,weight+stop_times[type]);
    network[ALL].addEdge(f,t,weight+stop_times[type]);
}

void TransportNetwork::print() {
    int counter;
    for(auto station = stations.begin(); station != stations.end(); ++station){
        auto& st = (*station);
        out << "--- Station: " << st->get_name() <<" ---\n";
        out << "Bus: ";
        counter = 0;
        auto edges = network[BUS].getNeighbors(st->getBusDockID());
        if (edges.size() == 0)   out << "NONE";
        for(auto edge = edges.begin(); edge != edges.end(); ++edge){
            if (counter != 0)   out << "\t";
            out << "(" << dockID_to_stationNAME(edge->first) << "," << edge->second.getWeight() << ")";
            counter++;
        }
        out << "\n";

        out << "Tram: ";
        counter = 0;
        edges = network[TRAM].getNeighbors(st->getTramDockID());
        if (edges.size() == 0)   out << "NONE";
        for(auto edge = edges.begin(); edge != edges.end(); ++edge){
            if (counter != 0)   out << "\t";
            out << "(" << dockID_to_stationNAME(edge->first) << "," << edge->second.getWeight() << ")";
            counter++;
        }
        out << "\n";

        out << "Sprinter: ";
        counter = 0;
        edges = network[SPRINTER].getNeighbors(st->getSprinterDockID());
        if (edges.size() == 0)   out << "NONE";
        for(auto edge = edges.begin(); edge != edges.end(); ++edge){
            if (counter != 0)   out << "\t";
            out << "(" << dockID_to_stationNAME(edge->first) << "," << edge->second.getWeight() << ")";
            counter++;
        }
        out << "\n";

        out << "Rail: ";
        counter = 0;
        edges = network[RAIL].getNeighbors(st->getRailDockID());
        if (edges.size() == 0)   out << "NONE";
        for(auto edge = edges.begin(); edge != edges.end(); ++edge){
            if (counter != 0)   out << "\t";
            out << "(" << dockID_to_stationNAME(edge->first) << "," << edge->second.getWeight() << ")";
            counter++;
        }
        out << "\n";
    }
}

void TransportNetwork::inbound(string name)  {
    int res_counter = 0;
    stringstream buf ;
    string str;
    inbound_helper(name,res_counter,buf);
    if (res_counter == 0)   out << "no inbound travel\n";
    else{
        buf >> str;
        out << str;
    }
}

void TransportNetwork::outbound(string name){
    int res_counter = 0;
    stringstream buf ;
    string str;
    outbound_helper(name,res_counter,buf);
    if (res_counter == 0)   out << "no outbound travel\n";
    else{
        buf >> str;
        out << str;
    }
}

void TransportNetwork::inbound_helper(string name, int& res_counter, stringstream& buf) {
    int station_id = -1;
    map<int,int> dockid;
    for(auto& station : stations){
        if (station->get_name().compare(name) == 0) {
            station_id = station->getId();
            dockid[BUS] = station->getBusDockID();
            dockid[TRAM] = station->getTramDockID();
            dockid[SPRINTER] = station->getSprinterDockID();
            dockid[RAIL] = station->getRailDockID();
            break;
        }
    }
    if (station_id == -1) throw invalid_argument(name+" station not found in the network");

    for (int type = 0; type < ALL; ++type) {
        Graph reverse(this->network[type].getReverse());
        auto di_result = reverse.Dijkstra(dockid[type]);

        buf << dock_types2name(type) << ": ";
        int counter = 0;
        //remof
        if (di_result == nullptr){
            buf << "\n";
            continue;
        }
        for(auto dock = di_result->begin(); dock != di_result->end(); ++dock){
            if( dock->second.first < infinity && dock->second.second != -1){
                res_counter++;
                if (counter != 0)   buf << "\t";
                buf << dockID_to_stationNAME(dock->first);
                counter++;
            }
        }
        buf << "\n";

    }


    return;
}

void TransportNetwork::outbound_helper(string name, int& res_counter, stringstream& buf){
    int station_id = -1;
    map<int,int> dockid;
    for(auto& station : stations){
        if (station->get_name().compare(name) == 0) {
            station_id = station->getId();
            dockid[BUS] = station->getBusDockID();
            dockid[TRAM] = station->getTramDockID();
            dockid[SPRINTER] = station->getSprinterDockID();
            dockid[RAIL] = station->getRailDockID();
            break;
        }
    }
    if (station_id == -1) throw invalid_argument(name+" station not found in the network");

    for (int type = 0; type < ALL; ++type) {
        auto di_result = network[type].Dijkstra(dockid[type]);

        buf << dock_types2name(type) << ": ";
        int counter = 0;
        if (di_result == nullptr){
            buf << "\n";
            continue;
        }
        for(auto dock = di_result->begin(); dock != di_result->end(); ++dock){
            if( dock->second.first < infinity && dock->second.second != -1){
                res_counter++;
                if (counter != 0)   buf << "\t";
                buf << dockID_to_stationNAME(dock->first);
                counter++;
            }
        }
        buf << "\n";
    }
}

void TransportNetwork::setStopTime(int type,int newST) {
    if (numOfStation != 0)  stop_times[type] = newST;
}

void TransportNetwork::setTransit(int type, int newT) {
    if (numOfStation != 0)  transits[type] = newT;
}

void TransportNetwork::load(string filename){
    int type = name_dock_to_type(filename);
    if (type == -1) throw invalid_argument("ERROR opening the specified file.\n");
    //open file
    ifstream file(filename);
    if (!file) throw invalid_argument("ERROR opening the specified file.\n");

    //read file to vector of string
    string str;
    vector<string> lines;
    vector<vector<string>> data;

    while (getline(file,str)) {
        lines.push_back(str);
    }

    for (auto st = lines.begin(); st != lines.end(); ++st){
        vector<string> temp;
        str = "";
        int counter = 0;
        int t_counter = 0;
        for(auto& ch : *st){
            if (ch == '\t'){
                if (counter == 0)   throw invalid_argument("ERROR opening the specified file.\n");
                t_counter++;
                temp.push_back(str);
                counter = 0;
                str = "";
                continue;
            }
            str += ch;
            counter++;
        }
        if(!(!str.empty() && find_if(str.begin(),str.end(), [](unsigned char c) { return !isdigit(c); }) == str.end()))
            throw invalid_argument("ERROR opening the specified file.\n");
        if( stoi(str) <= 0 ) throw invalid_argument("ERROR opening the specified file.\n");
        temp.push_back(str);
        if (t_counter != 2) throw invalid_argument("ERROR opening the specified file.\n");
        if (temp.size() != 3)   throw invalid_argument("ERROR opening the specified file.\n");
        data.push_back(temp);
    }

    //after all the check we can add new stations and line
    for(auto& t : data){
        if (getStationID(t[0]) == -1) {
            addStation(name_station_to_type(t[0]), t[0]);
        }
        if (getStationID(t[1]) == -1) {
            addStation(name_station_to_type(t[1]), t[1]);
        }
        addLine(type,t[0],t[1], stoi(t[2]));

    }






}

int TransportNetwork::getStationID(string name) {
    for(auto& station : stations)
        if (station->get_name().compare(name) == 0)
            return station->getId();
    return -1;
}

int TransportNetwork::name_station_to_type(string name) {
    if (name[0] == 'I' && name[1] == 'C')   return INTERCITY;
    if (name[0] == 'C' && name[1] == 'S')   return CENTRAAL;
    return STAD;
}

int TransportNetwork::name_dock_to_type(string name) {
    if (name.find("bus") != string::npos)   return BUS;
    if (name.find("sprinter") != string::npos)   return SPRINTER;
    if (name.find("rail") != string::npos)   return RAIL;
    if (name.find("tram") != string::npos)   return TRAM;
    return -1;

}

void TransportNetwork::uniExpress(string source, string target){
    map<int,int> toDOCKid_source;
    map<int,int> toDOCKid_target;

    int sourceID = -1, targetID = -1;
    for(auto& station : stations){
        if (station->get_name().compare(source) == 0) {
            sourceID = station->getId();
            toDOCKid_source[BUS] = station->getBusDockID();
            toDOCKid_source[TRAM] = station->getTramDockID();
            toDOCKid_source[SPRINTER] = station->getSprinterDockID();
            toDOCKid_source[RAIL] = station->getRailDockID();
        }
        if (station->get_name().compare(target) == 0){
            targetID = station->getId();
            toDOCKid_target[BUS] = station->getBusDockID();
            toDOCKid_target[TRAM] = station->getTramDockID();
            toDOCKid_target[SPRINTER] = station->getSprinterDockID();
            toDOCKid_target[RAIL] = station->getRailDockID();
        }
    }

    if (sourceID == -1)    throw invalid_argument("name of source not found");
    if (targetID == -1)    throw invalid_argument("name of target not found");

    for (int type = 0; type < ALL; ++type) {
        out << dock_types2name(type) << ": ";
        dijkstra_result dr = network[type].Dijkstra(toDOCKid_source[type]);
        for(auto iter = dr->begin(); iter != dr->end(); ++iter){
            if (iter->first == toDOCKid_target[type]){
                int dist = iter->second.first;
                if (dist == infinity)   out << "route unavailable.\n";
                else out << dist << ".\n";
                break;
            }
        }

    }

}

void TransportNetwork::multiExpress(string source, string target) {
    map<int,int> toDOCKid_source;

    int sourceID = -1, targetID = -1;
    for(auto& station : stations){
        if (station->get_name().compare(source) == 0) {
            sourceID = station->getId();
            toDOCKid_source[BUS] = station->getBusDockID();
            toDOCKid_source[TRAM] = station->getTramDockID();
            toDOCKid_source[SPRINTER] = station->getSprinterDockID();
            toDOCKid_source[RAIL] = station->getRailDockID();
        }
        if (station->get_name().compare(target) == 0){
            targetID = station->getId();
        }
    }

    if (sourceID == -1)    throw invalid_argument("name of source not found");
    if (targetID == -1)    throw invalid_argument("name of target not found");

    int minVal = infinity;
    for (int type = 0; type < ALL; ++type) {
        auto dr = network[ALL].Dijkstra(toDOCKid_source[type]);
        for(auto dock = dr->begin(); dock != dr->end(); ++dock ){
            if (dockID_to_stationID[dock->first] == targetID){
                if (minVal > dock->second.first)
                    minVal = dock->second.first;
            }
        }
    }
    if (minVal == infinity)   out << "route unavailable.\n";
    else out << "The shortest time is: " << minVal << ".\n";
}

TransportNetwork::~TransportNetwork() {
    out.close();

}








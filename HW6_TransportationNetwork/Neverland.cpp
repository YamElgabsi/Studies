//
// Created by YamEl on 5/22/2022.
//

#include "Neverland.h"
void exit(string msg){
    cerr << msg;
    exit(-1);
}

bool containsOnlyLetters(string const &str) {
    auto it = std::find_if(str.begin(), str.end(), [](char const &c) {
        return !std::isalpha(c);
    });
    return it == str.end();
}

bool isNumber(const string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}


int Run(int argc, char **argv) {
    vector<string> files;
    string config;
    string out = "output.dat";
    int phase = 1;
    bool isPhase2Started = false, isPhase3Started = false, isPhase2Completed = false, isPhase3Completed = false;
    if (argc < 2) exit("Too Few Arguments");

    string cur = argv[1];
    if (cur.compare("-i") != 0)  exit("Must start with -i");

    cur = argv[2];
    if (cur[0] == '-')  exit("After -i must be a filename");
    files.push_back(cur);

    for(int i = 3; i < argc; i++){
        cur = argv[i];
        if (cur == "-c"){
            phase = 2;
            isPhase2Started = true;
            continue;
        }

        if (cur == "-w"){
            phase = 3;
            isPhase3Started = true;
            continue;
        }

        if (phase == 1){
            if (cur[0] == '-')  exit("After -i must be a filename");
            files.push_back(cur);
            continue;
        }

        if (phase == 2){
            if (cur[0] == '-')  exit("After -c must be a filename");
            config = cur;
            isPhase2Completed = true;
            continue;
        }
        //if(phase == 3)
        if (cur[0] == '-')  exit("After -o must be a filename");
        out = cur;
        isPhase3Completed = true;

    }

    if (isPhase2Started && !isPhase2Completed) exit("cant read  -c without config file");

    if (isPhase3Started && !isPhase3Completed) exit("cant read  -o without out file");

    TransportNetwork transportNetwork(out);

    if (isPhase2Completed){//config
        ifstream file(config);
        vector<string> lines;
        if (!file) exit("can not open config file!");

        while (getline(file,config)) {
            lines.push_back(config);
        }

        for(auto& line : lines){
            config = "";
            bool isNum = false;
            string str, num;
            for(auto& ch : line){
                if (ch == ' '){
                    isNum = true;
                    continue;
                }
                if(isNum){
                    num += ch;
                    continue;
                }
                str += ch;
            }
            if (!isNum) exit("Wrong config file");
            if (!isNumber(num)) exit("Wrong config file");

            if (str.compare("bus") == 0){
                transportNetwork.setStopTime(BUS, stoi(num));
                continue;
            }

            if (str.compare("tram") == 0){
                transportNetwork.setStopTime(TRAM, stoi(num));
                continue;
            }

            if (str.compare("sprinter") == 0){
                transportNetwork.setStopTime(SPRINTER, stoi(num));
                continue;
            }

            if (str.compare("rail") == 0){
                transportNetwork.setStopTime(RAIL, stoi(num));
                continue;
            }

            if (str.compare("intercity") == 0){
                transportNetwork.setTransit(INTERCITY, stoi(num));
                continue;
            }

            if (str.compare("centraal") == 0){
                transportNetwork.setTransit(CENTRAAL, stoi(num));
                continue;
            }

            if (str.compare("stad") == 0){
                transportNetwork.setTransit(STAD, stoi(num));
                continue;
            }
            exit("Wrong config file");

        }
    }

    int file_counter = 1;
    for(auto& file : files ){
        try {
            transportNetwork.load(file);
        }
        catch ( ... ){
            exit("Can not read file number " + to_string(file_counter));
        }
        file_counter++;
    }

    cout << "PROGRAM READING COMPLETED!\n PLEASE MAKE A COMMEND:\n";
    string  str;
    string temp;
    getline(cin, str);
    while (str.compare("exit") != 0){
        temp = "";
        vector<string> split;
        for(auto& ch : str){
            if (ch == ' '){
                split.push_back(temp);
                temp = "";
                continue;
            }
            temp += ch;
        }
        split.push_back(temp);
        if (split.size() > 3){
            cerr << "WRONG COMMEND! PLEASE TRY AGAIN\n";
            getline(cin, str);
            continue;
        }
        if(split.size() == 2) {
            try {
                if (split[0].compare("load") == 0){
                    transportNetwork.load(split[1]);
                } else{
                    if (split[0].compare("outbound") == 0){
                        transportNetwork.outbound(split[1]);
                    } else{
                        if (split[0].compare("inbound") == 0){
                            transportNetwork.inbound(split[1]);
                        } else{
                            throw invalid_argument("WRONG COMMEND! PLEASE TRY AGAIN");
                        }
                    }
                }

            } catch (exception& e) {
                cerr << e.what();
                getline(cin, str);
                continue;

            }



        }

        if(split.size() == 3){
            try{
                if (split[0].compare("uniExpress") == 0) {
                    transportNetwork.uniExpress(split[1], split[2]);
                } else{
                    if (split[0].compare("multiExpress") == 0) {
                        transportNetwork.multiExpress(split[1], split[2]);
                    }
                    else{
                        throw invalid_argument("WRONG COMMEND! PLEASE TRY AGAIN");
                    }
            }


            }catch (exception& e){
                cerr << e.what();
                getline(cin, str);
                continue;

            }
            cout << "PLEASE MAKE THR NEXT COMMEND\n";
            getline(cin, str);
            continue;


        }

        if(split.size() == 1) {
            if (split[0].compare("print") != 0) {
                cerr << "WRONG COMMEND! PLEASE TRY AGAIN\n";
                getline(cin, str);
                continue;
            }
            transportNetwork.print();
            cout << "PLEASE MAKE THR NEXT COMMEND\n";
            getline(cin, str);
        }
    }



    return 0;
}

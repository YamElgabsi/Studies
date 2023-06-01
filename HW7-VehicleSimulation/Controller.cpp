//
// Created by Yam Elgabsi on 11/06/2022.
//

#include "Controller.h"

int inline command_to_enum(const string& str){
    if (str == "course")    return cmdCourse;
    if (str == "position")    return cmdPosition;
    if (str == "destination")    return cmdDestination;
    if (str == "attack")    return cmdAttack;
    if (str == "stop")    return cmdStop;
    if (str == "default")    return cmdDefault;
    if (str == "size")    return cmdSize;
    if (str == "zoom")    return cmdZoom;
    if (str == "pan")    return cmdPan;
    if (str == "show")    return cmdShow;
    if (str == "status")    return cmdStatus;
    if (str == "create")    return cmdCreate;
    if (str == "go")    return cmdGo;
    return -1;
}

void myExit(const string& str){
    cerr << str << endl;
    exit(1);
}


Controller::Controller(int argc, char** argv): model(Model::getInstance()), view(make_shared<View>()), files() {
    string frankfurt = "Frankfurt";
    model.generateWarehouse(frankfurt, {40, 10}, 100000);
    files.insert(files.end(), argv, argv + argc);
    check_warehouse();
    check_trucks();
    cout << fixed << showpoint;
    cout << setprecision(3);
}

bool Controller::get_command_from_user() {
    string command;
    cout << "Time " << model.getGameTime() << " Enter Command:" << endl;
    getline(cin,command);
    return parse_command(command);
}

bool Controller::parse_command(string& command) {
    string cmd;
    stringstream ss(command);

    if (command == "exit")  return false;

    ss >> cmd;
    try{
        if (model.findVehicle(cmd)){
            do_vehicle_command(ss, cmd);
            return true;
        }
        do_rest_command(ss, cmd);
        return true;
    }
    catch(MyException& e){}
    catch(ExitException& e){}
    catch(exception &e){
        cerr << "Invalid Command!" << endl;
        return true;
    }
    return true;
}

void Controller::Play() {
    while (get_command_from_user()) view->update();
    cout << "---turns off---";
}

void Controller::do_vehicle_command(stringstream& ss, string& name) {
    string cmd;
    ss >> cmd;

    vehicle_ptr vehicle = model.findVehicle(name);
    if (!vehicle)   throw MyException("Error! Vehicle Does Not Exist!\n");

    int _cmd = command_to_enum(cmd);
    if (_cmd == -1)  throw MyException("Error! Command Does Not Exist!\n");

    switch (_cmd) {
        case cmdCourse:{
            if(vehicle->getType() != CHOPPER)  throw MyException("Error! This function available only to choppers");
            double deg, speed;
            ss >> deg >> speed;
            if(speed > 170)   throw MyException("Error! Chopper's speed can not be higher then 170 km/h!");
            model.course(deg, speed, name);
            break;
        }

        case cmdPosition:{
            string x, y, speed;
            ss >> x >> y >> speed;
            stoi(x);  stoi(y);  stoi(speed);
            if (vehicle->getType() == CHOPPER) {
                if(stoi(speed) > 170)   throw MyException("Error! Chopper's speed can not be higher then 170 km/h!");
                model.position(x, y, vehicle, stoi(speed));
                return;
            }
            model.position(x, y, vehicle);
            break;
        }

        case cmdDestination:{
            string wh;
            ss >> wh;
            if (!model.findWareHouse(wh))   throw MyException("Error! Warehouse does not exist!");
            model.destination(wh, vehicle);
            break;
        }

        case cmdAttack:{
          string truck;
          ss >> truck;
          model.attack(truck, vehicle);
          break;
        }

        case cmdStop:{
            model.stop(vehicle);
            break;
        }


    }
}

void Controller::check_warehouse() {
  string line, name, x, y, file;
  int inventory;

  for(auto iter = files.begin(); iter != files.end(); ++iter) {
      if (*iter == "-w") {
          file = *++iter;
          break;
      }
  }

  ifstream wFile(file);
  while(getline(wFile,line)) {
      try{
          stringstream ss(line);
          ss >> name >> x >> y >> inventory;
          name = name.substr(0, name.size() - 1);
          x = x.substr(1, x.size() - 2);
          y = y.substr(0, y.size() - 2);
          model.generateWarehouse(name, {stof(x), stof(y)}, inventory);
      }

      catch (...){
          myExit("Error! Invalid warehouse file!");
      }
    }

}

void Controller::do_rest_command(stringstream& ss, string &cmd) {
    int _cmd = command_to_enum(cmd);
    if (_cmd == -1)  throw MyException("Error! Command does not Exist!");

    switch (_cmd) {
        case cmdDefault: {
            view->setDefault();
            break;
        }
        case cmdSize: {
            int size;
            ss >> size;
            if(size < 6 || size > 30)   throw MyException("Error! the size need to be between 6 and 30!");
            view->setSize(size);
            break;
        }
        case cmdZoom: {
            float scale;
            ss >> scale;
            if(scale < 0)   throw MyException("Error! The map's scale is a positive number!");
            view->setScale(scale);
            break;
        }
        case cmdPan: {
            int x,y;
            ss >> x >> y;
            view->setX(x);
            view->setY(y);
            break;
        }
        case cmdShow: {
            view->show();
            break;
        }
        case cmdStatus: {
            model.status();
            break;
        }
        case cmdCreate: {
            string name, type, x, y, wh;
            ss >> name >> type;

            if (name.size() > 12)    throw MyException("Error! Vehicle name can not have more then 12 chars!");

            if (type == "Chopper") {
                ss >> x >> y;
                x = x.substr(1, x.size() - 2);
                y = y.substr(0, y.size() - 1);
                Point p(stof(x), stof(y));
                model.generateChopper(name, p);
                break;
            }
            ss >> wh;
            model.generateStateTrooper(name, wh);
            break;
        }
        case cmdGo:{
            model.go();
        }

    }
}




void Controller::check_trucks() {
    string line, name, nextStop, arriveTime, leaveTime, prevLeaveTime, p;
    int idx, crates = 0;
    double time;
    routes_vector routes;
    schedule_vector  times;
    idx = get_truck_index_files();
    while(idx != files.size()){
        ifstream tFile(files[idx]);
        parseFirstLine(line ,idx, name, p, tFile);
        stringstream ss(line);
        ss >> p;
        prevLeaveTime = "00:00";

        while (getline(tFile,line)){
            parseLine(line, nextStop, arriveTime, crates, leaveTime);
            model.findWareHouse(nextStop);
            time = getTime(prevLeaveTime,arriveTime , leaveTime);
            prevLeaveTime = leaveTime;
            routes.emplace_back(nextStop, make_pair(time,crates));
            times.emplace_back(arriveTime,leaveTime);
        }
        model.generateTruck(p, name, routes, times);
        idx++;

    }
}

int Controller:: get_truck_index_files(){
    int index = 0;
    for(auto & _file : files) {
        index++;
        if (_file == "-t")
            return index;
    }
    return index;
}

double Controller::getTime(string &start, string &end, string & leave) {
    start.erase(remove(start.begin(), start.end(), ':'), start.end());
    end.erase(remove(end.begin(), end.end(), ':'), end.end());
    leave.erase(remove(leave.begin(), leave.end(), ':'), leave.end());
    int s = stoi(start);
    int e = stoi(end);
    int first_time_min = s / 100 * 60 + s % 100;
    int second_time_min = e / 100 * 60 + e % 100;
    return (second_time_min - first_time_min) / 60.0;
}

void Controller::parseLine(string &line, string &nextStop, string &arriveTime, int &crates, string &leaveTime) {
    std::replace( line.begin(), line.end(), ',', ' ');
    stringstream ss(line);
    ss >> nextStop >> arriveTime >> crates >> leaveTime;
}

void Controller::parseFirstLine(string& line, int idx, string &truckName, string &startingPoint, ifstream &truckFile) {
    truckName = files[idx].substr(0, files[idx].size() - 4); // name of truck
    getline(truckFile,line);
    std::replace( line.begin(), line.end(), ',', ' ');
}




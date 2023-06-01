//
// Created by YamEl on 5/18/2022.
//

#include "Station.h"
int Station::station_counter = 0;

Station::Station(int type, string name) :name(name), type(type),id(station_counter++){
    if (type !=  INTERCITY && type != CENTRAAL && type != STAD) {
        cout << ("The type must to be from the stations type enum!\n");
        exit(-1);
    }
    bus_dock = unique_ptr<Dock>(new BusDock());
    tram_dock = unique_ptr<Dock>(new TramDock());
    sprinter_dock = unique_ptr<Dock>(new SprinterDock());
    rail_dock = unique_ptr<Dock>(new RailDock());
}


string Station::get_name() const {
    return name;
}

void Station::print_name() const {
    cout<<name;
}

int Station::getId() const {
    return id;
}

int Station::getBusDockID() const {
    return bus_dock->getId();
}

int Station::getTramDockID() const {
    return tram_dock->getId();
}

int Station::getSprinterDockID() const {
    return sprinter_dock->getId();
}

int Station::getRailDockID() const {
    return rail_dock->getId();
}

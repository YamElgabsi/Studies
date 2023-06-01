//
// Created by YamEl on 5/18/2022.
//

#ifndef HW02_STATION_H
#define HW02_STATION_H

#include "BusDock.h"
#include "TramDock.h"
#include "SprinterDock.h"
#include "RailDock.h"

enum stations_types{INTERCITY, CENTRAAL, STAD};


class Station {

private:
    //--ID--:
    string name;
    int type;
    const int id;
    static int station_counter;//for constructors

    //--Docks--:
    unique_ptr<Dock> bus_dock;
    unique_ptr<Dock> tram_dock;
    unique_ptr<Dock> sprinter_dock;
    unique_ptr<Dock> rail_dock;

public:
    //--The Big Five--:
    Station(int type, string name = "NO NAME");
    Station() = delete;
    virtual ~Station() = default;
    Station(const Station& other) = delete;
    Station& operator=(const Station& other) = delete;
    Station(const Station&& other) = delete;

    //--Getters--
    string get_name() const;
    int getId() const;
    int getBusDockID() const;
    int getTramDockID() const;
    int getSprinterDockID() const;
    int getRailDockID() const;

    //--Prints--
    void print_name() const;
    virtual void printID() const = 0;


};


#endif //HW02_STATION_H


#ifndef EX03_MODEL_H
#define EX03_MODEL_H

#include "SimObjFactory.h"
#include "vector"
#include <memory>

struct MyException:public exception{
    explicit MyException(const string& msg)
    {cerr << msg;}
};

struct ExitException:public exception{
    explicit ExitException(const string& msg)
    {cerr << msg << endl << "---turns off---" << endl;
        exit(1);}
};

using namespace std;

using schedule_vector = vector< pair<string,string> >;
using routes_vector = vector < pair<string, pair<double, int> > >;


class Model{
private:
    int gameTime;
    vector<simObject_ptr> simObjects;
    vector<vehicle_ptr> vehicles;
    vector<warehouse_ptr> warehouses;
    shared_ptr<SimObjFactory> simObjFactory;

protected:
    Model();
    static unique_ptr<Model> instance;

public:
    static Model& getInstance();

    // --The Big 5--
    ~Model() = default;
    Model(const Model&) = delete;
    Model& operator= (const Model&) = delete;
    Model(const Model&&) = delete;
    Model& operator= (const Model&&) = delete;


    //--Getters--
    vector<simObject_ptr>* getSimObjects() {return &simObjects;};
    int getGameTime() const;

    //--Functions--
    void course(double degree, double speed, string& vehicleName);
    void position(const string& x, const string& y, vehicle_ptr& vehicle, int speed = 0);
    void destination(const string& warehouse, vehicle_ptr& vehicle);
    void attack(const string& truck, vehicle_ptr& vehicle);
    static void stop(vehicle_ptr& vehicle);
    void go();
    void status();

    //--Generate Functions--
    void generateTruck(string &startingPoint, string &name, const routes_vector & routes, schedule_vector &times);
    void generateWarehouse(string &name, const Point& point, int capacity);
    void generateChopper(string &name, Point &startingPoint);
    void generateStateTrooper(string &name, string &warehouse);

    //--Helpers Functions--
    void printWarehousesStatus();
    void printVehiclesStatus();
    vehicle_ptr findVehicle(const string &name) const;
    warehouse_ptr findWareHouse(const string& name) const;
};


#endif //EX03_MODEL_H

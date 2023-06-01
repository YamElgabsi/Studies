//
// Created by Yam Elgabsi on 11/06/2022.
//
#include <exception>
#include "Model.h"

unique_ptr<Model> Model::instance;

Model::Model(): gameTime(0), simObjects(), vehicles(), warehouses(), simObjFactory(new SimObjFactory()) {
}

Model &Model::getInstance() {
    if (instance == nullptr)        instance =std::unique_ptr<Model>(new Model());
    return *(instance);
}

int Model::getGameTime() const {return gameTime;}

vehicle_ptr Model::findVehicle(const string &name) const {
   for(auto& v: vehicles)       if (v->getName() == name)           return v;

   return nullptr;
}

warehouse_ptr Model::findWareHouse(const string &name) const {
  for(auto& w: warehouses)    if(w->getName() == name)      return w;
  return nullptr;
}

void Model::generateWarehouse(string &name, const Point &point, int capacity) {

  auto wh = make_shared<Warehouse>(name, point, capacity);
  warehouses.emplace_back(wh);
  simObjects.emplace_back(wh);
}


void Model::generateTruck(string &startingPoint, string &name, const routes_vector & routes, schedule_vector &times) {
    Point p(findWareHouse(startingPoint)->getLocation()->getX(), findWareHouse(startingPoint)->getLocation()->getY());
    auto  newTruck = (simObjFactory->create(name, p, TRUCK));
    shared_ptr<Truck> nt = dynamic_pointer_cast<Truck>(newTruck);
    nt->setRoutes(routes);    nt->setTimes(times);
    nt->motionCalculations();
    simObjects.emplace_back(newTruck);
    vehicles.emplace_back(newTruck);
}

void Model::status() {
    printWarehousesStatus();
    printVehiclesStatus();
}

void Model::printWarehousesStatus() {
    for(auto &wHouse : warehouses){
        cout << wHouse->getName() << " at position ";
        wHouse->printLocation();
        cout << ", Inventory: " << wHouse->getCapacity() << endl;
    }
}

void Model::printVehiclesStatus() {
    for(auto &vehicle : vehicles){
        cout << vehicle->getType() << " " << vehicle->getName() << " at ";
        vehicle->printLocation();
        vehicle->getStatus();
    }
}

void Model::course(double degree, double speed, string &vehicleName)  {
    vehicle_ptr chopper =  findVehicle(vehicleName);
    chopper->setCourse(degree);
    chopper->setSpeed(speed);
}

void Model::generateChopper(string &name, Point &startingPoint) {
    if (findVehicle(name))        throw MyException("Error! Already exists vehicle with the same name!");

    auto newChopper = (simObjFactory->create(name, startingPoint, CHOPPER));
    simObjects.emplace_back(newChopper);
    vehicles.emplace_back(newChopper);
}

void Model::generateStateTrooper(string &name, string &warehouse) {
    auto newTrooper = simObjFactory->create(name, *findWareHouse(warehouse)->getLocation(), STATE_TROOPER);
    dynamic_pointer_cast<StateTrooper>(newTrooper)->init(warehouses, findWareHouse(warehouse));
    newTrooper->setSpeed(90);
    simObjects.emplace_back(newTrooper);
    vehicles.emplace_back(newTrooper);
}

void Model::position(const string& x, const string& y, vehicle_ptr &vehicle, int speed) {
    vehicle->setState(POSITION);
    vehicle->setTarget(x + " " + y);
    Point p = vehicle->getTargetPoint();
    vehicle->setCourse(angle_between(*vehicle->getLocation(), p));
    if(speed)
        vehicle->setSpeed(speed);
}
void Model::attack(const string &truck, vehicle_ptr &vehicle) {
    vehicle_ptr truckPtr = findVehicle(truck);
    dynamic_pointer_cast<Chopper>(vehicle)->attack(truckPtr);
}

void Model::destination(const string &warehouse, vehicle_ptr &vehicle) {
    if(vehicle->getType() != STATE_TROOPER)        throw MyException("Error! This command is only valid  for State Troopers!");
    dynamic_pointer_cast<StateTrooper>(vehicle)->setNextVisit(findWareHouse(warehouse));
}

void Model::go() {
    gameTime++;
    for(auto obj : vehicles)        obj->update();


}

void Model::stop(vehicle_ptr &vehicle) {vehicle->setState(STOPPED);}





//
// Created by YamEl on 12/15/2021.
//Based on Tal Abziz's int LinkedList that we saw in Lab07
//

#ifndef HW03_CARLINKEDLIST_H
#define HW03_CARLINKEDLIST_H

#include <iostream>
#include "Car.h"
#include <iostream>

using namespace std;

class CarLinkedList {

private:
    struct Node {
        Car car;
        Node* next;

        Node(Car car, Node* next);
    };

    Node* head;
    int count;

public:

    /**
     * Create an empty list of cars
     */
    CarLinkedList();

    /* big three */
    CarLinkedList(const CarLinkedList& other);

    CarLinkedList& operator=(const CarLinkedList& rhs);

    ~CarLinkedList();

    /**
     * insert an car to the head of the list (a copy of the car with the same id)
     * @param car
     */
    void insert(Car car);

    /**
     * remove the first occurrence of elem in the list
     * @param carId
     */
    void remove(int carId);

    /**
     * remove all elements from the list
     */
    void clear();

    /**
     * return how many elements are in the list
     */
    int size() const;

    /**
     * access an element at a given index
     * @param index
     * @return
     */
    Car& operator[](int index);


    /**
     * return an element at a given index
     * @param index
     * @return
     */
    const Car& operator[](int index) const;

    friend ostream& operator<<(ostream& out, const CarLinkedList& list);


};

ostream& operator<<(ostream& out, const CarLinkedList& list);



#endif //HW03_CARLINKEDLIST_H

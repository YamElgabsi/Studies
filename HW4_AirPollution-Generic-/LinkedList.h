//
// Created by YamEl on 12/29/2021.
//

#ifndef HW04_LINKEDLIST_H
#define HW04_LINKEDLIST_H

#include <iostream>
using namespace std;

/**
 * Generic LinkedList<T> sorted
 * operators that T need to support: << ,  < , ==
 */
template<class T>
class LinkedList {

private:
    struct Node {
        T* tPointer;
        Node* next;

        Node(T* tPointer, Node* next):tPointer(tPointer), next(next){}
        ~Node(){delete tPointer;}
    };

    Node* head;
    int count;

public:

    /**
     * Create an empty list
     */
    LinkedList();

    /* big three */
    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);
    ~LinkedList();

    /**
     * insert an value T to the list sorted by order
     * if the element already in the list do nothing
     * @param value
     */
    void insert(T value);



    /**
     * remove the first occurrence of elem in the list
     * @param elem
     */
    void remove(T elem);

    /**
     * remove all elements from the list
     */
    void clear();

    /**
     * return how many elements are in the list
     */
    int size() const;

    /**
     * return true if the value is already in the list, else false
     * @param value
     */
    bool isContain(T value);

    /**
     * access an element at a given index
     * @param index
     * @return
     */
    T& operator[](int index);


    /**
     * return an element at a given index
     * @param index
     * @return
     */
    const T& operator[](int index) const;



};

template <class T>
ostream& operator<<(ostream& out, const LinkedList<T>& list);



#endif //HW04_LINKEDLIST_H

#include "LinkedList_imp.h"


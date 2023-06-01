//
// Created by YamEl on 12/29/2021.
//

#ifndef HW04_MAP_H
#define HW04_MAP_H

#include <iostream>
using namespace std;

/**
 * Generic Map<class K, class V>
 * K is the Key Class, V is the Value class;
 * operators that K and V needs to support: <<, < , ==
 */
template<class K, class V>
class Map {
private:
    struct Node {
        K* keyPointer;
        V* valuePointer;
        Node* next;

        Node(K* keyPointer, V* valuePointer, Node* next):keyPointer(keyPointer), valuePointer(valuePointer), next(next){}
        ~Node(){delete keyPointer; delete valuePointer;}
        void setKey(K* newKeyPointer){delete keyPointer; keyPointer = newKeyPointer;}
        void setVal(V* newValPointer){delete valuePointer; valuePointer = newValPointer;}
    };

    Node* head;
    int count;

public:

    /**
     * Create an empty map
     */
    Map();

    /* big three */
    Map(const Map& other);
    Map& operator=(const Map& other);
    ~Map();

    /**
     * insert an value V to the map sorted by order of keys
     * if the key is already in the map change the value
     * @param key
     * @param value
     */
    void insert(K key, V value);

    /**
     * return pointer to value of giving key
     * if the key is not in the map return NULL
     * @param key
     */
    V* find(K key);



    /**
     * remove the occurrence of element in the map by key
     * @param key
     */
    void remove(K key);

    /**
     * remove all elements from the map
     */
    void clear();

    /**
     * return how many elements are in the map
     */
    int size() const;

    /**
     * return true if the kay is already in the map, else false
     * @param value
     */
    bool isContain(K key);

    /**
     * access a value of element at a given Key
     * @param Key
     * @return
     */
    V* operator[](K key);


    /**
     * return a value of element at a given key
     * @param key
     * @return
     */
    const V* operator[](K key) const;

    /**
     * return a string who present the map
     * @return string
     */
    string& toString() const;

    /**
     * print the map
     */
    void print() const;



};

template <class K, class V>
ostream& operator<<(ostream& out, const Map<K,V>& map);


#endif //HW04_MAP_H

#include "Map_imp.h"

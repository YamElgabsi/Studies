//
// Created by YamEl on 12/31/2021.
//

#ifndef HW04_MAP_IMP_H
#define HW04_MAP_IMP_H


#include "Map.h"
#include <cstdlib>
#include <sstream>


template <class K, class V>
Map<K,V>::Map() : head(NULL), count(0) {}

template <class K, class V>
void Map<K,V>::insert(K key, V value){
    Node* cursor = head;
    if (isContain(key)) {
        while(cursor != NULL){
            if(key == *(cursor->keyPointer)){
                cursor->setVal(new V(value));
                return;
            }
            cursor = cursor->next;
        }
    }
    if(count == 0) {
        head = new Node(new K(key), new V(value), NULL);
        count++;
        return;
    }

    cursor = head;
    while(cursor->next != NULL){
        if(key < *(cursor->keyPointer))
            break;
        cursor = cursor->next;
    }
    if (*(cursor->keyPointer) < key)
        cursor->next = new Node(new K(key), new V(value), cursor->next);
    else {
        K* tempK = cursor->keyPointer;
        V* tempV = cursor->valuePointer;
        cursor->keyPointer = new K(key);
        cursor->valuePointer = new V(value);
        cursor->next = new Node(tempK, tempV, cursor->next);
    }
    count++;
}

template<class K, class V>
V* Map<K,V>::find(K key) {
    if (!isContain(key))  return NULL;

    Node* cursor = head;
    while (cursor){
        if (key == *(cursor->keyPointer))
            break;
        cursor = cursor->next;
    }
    return cursor->valuePointer;
}


template <class K, class V>
void Map<K,V>::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    count = 0;
    head = NULL;
}
template<class K, class V>
Map<K,V>::Map(const Map<K,V>& other) : head(NULL), count(0) {
    Node* cursor = other.head;
    while (cursor) {
        insert(*(cursor->keyPointer), *(cursor->valuePointer));
        cursor = cursor->next;
    }
}
template<class K, class V>
Map<K,V>& Map<K,V>::operator=(const Map& rhs) {
    if (this != &rhs) {
        clear();
        Node* temp = rhs.head;
        while (temp) {
            insert(*(temp->keyPointer, *(temp->valuePointer)));
            temp = temp->next;
        }
    }
    return *this;
}

template<class K, class V>
Map<K,V>::~Map() {
    clear();
}

template<class K, class V>
V* Map<K,V>::operator[](K key) {
    if (!isContain(key))  return NULL;

    Node* cursor = head;
    while (cursor){
        if (key == *(cursor->keyPointer))
            break;
        cursor = cursor->next;
    }
    return cursor->valuePointer;
}
template<class K, class V>
const V* Map<K,V>::operator[](K key) const {
    if (!isContain(key)) return NULL;
    Node* cursor = head;
    while (cursor){
        if (key == *(cursor->keyPointer))
            break;
        cursor = cursor->next;
    }
    return cursor->valuePointer;
}

template<class K, class V>
string& Map<K,V>::toString() const{
    Node* cursor = head;
    string* str = new string("{");
    for (int i = 0; i < size(); ++i) {
        if (i != 0)
            *str += " , ";
        stringstream elm;
        elm << *(cursor->keyPointer) << ":" << *(cursor->valuePointer);
        string temp;
        elm >> temp;
        *str += temp;
        cursor = cursor->next;
    }
    *str += "}";
    return *str;
}

template<class K, class V>
ostream& operator<<(ostream& out, const Map<K,V>& map) {
    out << map.toString();
    return out;
}

template<class K, class V>
void Map<K,V>::remove(K key) {
    if (!head) { return; }
    Node* temp = head;
    if ( *(temp->keyPointer) == key) {
        head = head->next;
        delete temp;
        count--;
        return;
    }
    while (temp->next && *(temp->next->keyPointer) != key) {
        temp = temp->next;
    }
    if (temp->next) {
        Node* victim = temp->next;
        temp->next = victim->next;
        delete victim;
        count--;
    }
}

template<class K, class V>
bool Map<K,V>::isContain(K key){
    Node* cursor = head;
    while (cursor){
        if (*(cursor->keyPointer) == key)
            return true;
        if (key < *(cursor->keyPointer))//the list is sorted by value and the node is bigger
            break;
        cursor = cursor->next;
    }
    return false;
}
template<class K, class V>
int Map<K,V>::size() const {
    return count;
}

template<class K, class V>
void Map<K,V>::print() const {
    std::cout << toString();
}

#endif //HW04_MAP_IMP_H

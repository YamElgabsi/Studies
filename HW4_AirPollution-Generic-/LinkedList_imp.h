//
// Created by YamEl on 12/29/2021.
//



#ifndef HW04_LINKEDLIST_IMP_H
#define HW04_LINKEDLIST_IMP_H

#include "LinkedList.h"
#include <cstdlib>


template <class T>
LinkedList<T>::LinkedList() : head(NULL), count(0) {}

template <class T>
void LinkedList<T>::insert(T value){
    if (isContain(value))   return;
    if(count == 0) {
        head = new Node(new T(value), NULL);
        count++;
        return;
    }

    Node* cursor = head;
    while(cursor->next != NULL){
        if(value < *(cursor->tPointer))
            break;
        cursor = cursor->next;
    }
    if (*(cursor->tPointer) < value)
        cursor->next = new Node(new T(value), cursor->next);
    else {
        T* temp = cursor->tPointer;
        cursor->tPointer = new T(value);
        cursor->next = new Node(temp, cursor->next);
    }
    count++;
}


template <class T>
void LinkedList<T>::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    count = 0;
    head = NULL;
}
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(NULL), count(0) {
    Node* cursor = other.head;
    while (cursor) {
        insert(*(cursor->tPointer));
        cursor = cursor->next;
    }
}
template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& rhs) {
    if (this != &rhs) {
        clear();
        Node* temp = rhs.head;
        while (temp) {
            insert(*(temp->tPointer));
            temp = temp->next;
        }
    }
    return *this;
}
template <class T>
LinkedList<T>::~LinkedList() {
    clear();
}
template <class T>
T& LinkedList<T>::operator[](int index) {
    if (index < 0 || index >= count) {
        cerr << "whoa there buddy!" << endl;
        exit(1);
    }
    Node* temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return *(temp->tPointer);
}
template <class T>
const T& LinkedList<T>::operator[](int index) const {
    if (index < 0 || index >= count) {
        cerr << "whoa there buddy" << endl;
        exit(1);
    }
    Node* temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return *(temp->tPointer);
}

template <class T>
ostream& operator<<(ostream& out, const LinkedList<T>& list) {
    for (int i = 0; i < list.size(); ++i) {
        if (i != 0) {
            out << ",";
        }
        out << list[i];
    }
    return out;
}

template <class T>
void LinkedList<T>::remove(T elem) {
    if (!head) { return; }
    Node* temp = head;
    if ( *(temp->tPointer) == elem) {
        head = head->next;
        delete temp;
        count--;
        return;
    }
    while (temp->next && *(temp->next->tPointer) != elem) {
        temp = temp->next;
    }
    if (temp->next) {
        Node* victim = temp->next;
        temp->next = victim->next;
        delete victim;
        count--;
    }
}

template <class T>
bool LinkedList<T>::isContain(T value){
    Node* cursor = head;
    while (cursor){
        if (*(cursor->tPointer) == value)
            return true;
        if (value < *(cursor->tPointer))//the list is sorted by value and the node is bigger
            break;
        cursor = cursor->next;
    }
    return false;
}
template <class T>
int LinkedList<T>::size() const {
    return count;
}


#endif //HW04_LINKEDLIST_IMP_H

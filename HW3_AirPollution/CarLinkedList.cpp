//
// Created by YamEl on 12/15/2021.
//

#include "CarLinkedList.h"
#include <cstdlib>

CarLinkedList::CarLinkedList() : head(NULL), count(0) {}

void CarLinkedList::insert(Car car) {
    count++;
    if(count == 1) {
        head = new Node(Car(car), NULL);
        return;
    }
    Node* courser = head;
    while (courser->next != NULL)
        courser = courser->next;
    courser->next = new Node(Car(car), NULL);
}

void CarLinkedList::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    count = 0;
    head = NULL;
}

CarLinkedList::CarLinkedList(const CarLinkedList& other) : head(NULL), count(0) {
    Node* temp = other.head;
    while (temp) {
        insert(temp->car);
        temp = temp->next;
    }
}

CarLinkedList& CarLinkedList::operator=(const CarLinkedList& rhs) {
    if (this != &rhs) {
        clear();
        Node* temp = rhs.head;
        while (temp) {
            insert(temp->car);
            temp = temp->next;
        }
    }
    return *this;
}

CarLinkedList::~CarLinkedList() {
    clear();
}

Car& CarLinkedList::operator[](int index) {
    if (index < 0 || index >= count) {
        cerr << "whoa there buddy!" << endl;
        exit(1);
    }
    Node* temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp->car;
}

const Car& CarLinkedList::operator[](int index) const {
    if (index < 0 || index >= count) {
        cerr << "whoa there buddy" << endl;
        exit(1);
    }
    Node* temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp->car;
}

ostream& operator<<(ostream& out, const CarLinkedList& list) {
    CarLinkedList::Node* temp = list.head;
    while (temp) {
        if (temp != list.head) {
            out << ",";
        }
        out << temp->car;
        temp = temp->next;
    }
    return out;
}

void CarLinkedList::remove(int elem) {
    if (!head) { return; }
    Node* temp = head;
    if (temp->car.getId() == elem) {
        head = head->next;
        delete temp;
        count--;
        return;
    }
    while (temp->next && temp->next->car.getId() != elem) {
        temp = temp->next;
    }
    if (temp->next) {
        Node* victim = temp->next;
        temp->next = victim->next;
        delete victim;
        count--;
    }
}

int CarLinkedList::size() const {
    return count;
}

CarLinkedList::Node::Node(Car car, Node* next) : car(car), next(next) {}
//
// Created by YamEl on 12/15/2021.
//

#include "Junction.h"

//Constructor
Junction::Junction(unsigned int id) : id(id){}

//Getters
unsigned int Junction::getId() const {
    return id;
}


//Setters
void Junction::setId(unsigned int id) {
    Junction::id = id;
}


//operators
bool operator<(const Junction& lhs, const Junction& rhs){
    return lhs.getId()<rhs.getId();
}
bool operator==(const Junction& lhs, const Junction& rhs){
    return lhs.getId()==rhs.getId();
}

ostream& operator<<(ostream& out, const Junction& junction){
    out << junction.id;
    return out;
}
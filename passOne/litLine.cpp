//
// Created by HP on 06-Jun-18.
//

#include "litLine.h"
void litLine :: setLiteral (string t){
    literal = t;
}
string litLine :: getLiteral (void){
    return literal;
}


void litLine :: setValue (string t){
    value = t;

}
string litLine :: getValue (void){
    return value;
}


void litLine :: setLength (string t){
    length = t;
}
string litLine :: getLength (void){
    return length;
}


void litLine :: setAddress (string t){
    address = t;
}
string litLine :: getAddress (void){
    return address;
}



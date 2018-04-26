//
// Created by HP on 24-Apr-18.
//

#include "../Row.h"

void Row :: setLabel (string lab){
    label = lab;
}
string Row :: getLabel (void){
    return label ;
}


void Row ::setOperand (string op) {
    operand = op;
}
string Row :: getOperand (void){
    return operand ;
}

void Row :: setop_code (string op_cd){
    op_code = op_cd;
}
string Row :: getop_code (void){
    return op_code ;
}


void Row :: setcomment (string t){
    comment = t;
}
string Row :: getcomment (void){
    return comment ;
}


void Row :: setAddress (string Ad){
    Address = Ad;
}
string Row :: getAddress (void){
    return Address ;
}



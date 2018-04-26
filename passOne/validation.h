//
// Created by king on 4/26/2018.
//

#ifndef PASSONE_VALIDATION_H
#define PASSONE_VALIDATION_H
#include <cstring>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "Row.h"

using namespace std ;

class validation {



private:
    string operator;
    string comment;
    string operand;
    string label ;
    vector <string> labels ;
    list<map<string, string>> TheParsinglist;
    list<Row> validationRows;

public:

    void setParsinglist(list<map<string, string>> list1);
    string getLabel ();
    void  validate(void);
    list<Row>getValidationMap(void);



};


#endif //PASSONE_VALIDATION_H

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
#include "Line.h"

using namespace std ;

class validation {



private:
    string operat;
    string comment;
    string operand;
    string label ;
    vector <string> labels ;
    list<Line> TheParsinglist;
    list<Row> validationRows;

public:

    void setParsinglist(list<Line>list1);
    string getLabel ();
    void  validate(void);
    list<Row>getValidationMap(void);



};


#endif //PASSONE_VALIDATION_H

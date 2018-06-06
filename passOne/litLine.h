//
// Created by HP on 06-Jun-18.
//

#ifndef PASSONE_LITLINE_H
#define PASSONE_LITLINE_H


#include <cstring>
#include <string>
using namespace std;
class litLine {

private:
    string literal="null";
    string value="null";
    string length="null";
    string address="null";

public:

    void setLiteral(string);
    string getLiteral(void);

    void setValue(string);
    string getValue(void);
    void setLength(string);
    string getLength(void);
    void setAddress(string);
    string getAddress(void);



};


#endif //PASSONE_LITLINE_H

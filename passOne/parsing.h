//
// Created by HP on 28-Apr-18.
//

#ifndef PASSONE_PARSING_H
#define PASSONE_PARSING_H
#include <cstring>
#include <string>
#include <vector>
#include <list>
#include "Line.h"

class parsing {
public:

    list<Line> parisngFunction(string );

    size_t split(const std::string &txt, std::vector<std::string> &strs, char ch);
    bool startsWith (string line, string charsStartWith);

    void printTheList (list<Line> aaaaa);
};


#endif //PASSONE_PARSING_H

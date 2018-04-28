//
// Created by HP on 28-Apr-18.
//

#ifndef PASSONE_PARSING_MAP_H
#define PASSONE_PARSING_MAP_H

//
// Created by Magho on 27-Apr-18.
//

#include <cstring>
#include <string>
#include <vector>
#include <list>
#include <map>

using namespace std;

class parsing_map {

public:

    list<map<string, string>> parisngFunction(string );

    size_t split(const std::string &txt, std::vector<std::string> &strs, char ch);
    bool startsWith (string line, string charsStartWith);

    void printTheList (list<map<string, string>> aaaaa);
};



#endif //PASSONE_PARSING_MAP_H

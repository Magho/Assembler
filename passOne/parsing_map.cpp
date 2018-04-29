//
// Created by HP on 28-Apr-18.
//

#include "parsing_map.h"
//
// Created by Magho on 27-Apr-18.
//

#include <fstream>
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <algorithm>

list<map<string, string>> parsing_map :: parisngFunction (string path) {

    ifstream file;
    // path --> "/home/magho/workspaceC++/Assembler/passOne/test.txt"
    file.open(path, ios::in);

    list<map<string, string>> aaaaa;
    vector<string> string1;
    std::string str;

    try {

        while (std::getline(file, str)) {

            map<string, string> bbbb;

            //transfer to string to lower case
            std::transform(str.begin(), str.end(), str.begin(), ::tolower);

            //check if comment line
            if (startsWith(str, ".")) {

                bbbb.insert(std::pair<string, string>("commentonly", "true"));
                bbbb.insert(std::pair<string, string>("comment", str));

            } else if (str.size() == 0) {

                bbbb.insert(std::pair<string, string>("error", "true"));

            } else {

                split(str, string1, ' ');

                cout << "\n";
                for (int i = 0; i < string1.size(); i++) {

                    if (startsWith(string1[i], ".")) {
                        string str123 = "";
                        for (int j = i; j < string1.size(); j++) {
                            str123 = str123 + string1[j] + " ";
                        }
                        //remove the extra space at the end
                        str123 = str123.substr(0, str123.size() - 1);
                        bbbb.insert(std::pair<string, string>("comment", str123));

                        break;
                    } else if (i == 0) {
                        char x = string1[i][0];
                        if ((int(x) >= 65 && int(x) <= 90 )| (int(x) <= 122 && int(x) >= 97) ) {
                            bbbb.insert(std::pair<string, string>("word1", string1[i]));
                        } else {
                            bbbb.insert(std::pair<string, string>("error", "true"));
                            break;
                        }
                    }
                    else if (i == 1)
                        bbbb.insert(std::pair<string, string>("word2", string1[i]));
                    else if (i == 2)
                        bbbb.insert(std::pair<string, string>("word3", string1[i]));
                    else {
                        bbbb.insert(std::pair<string, string>("error", "true"));
                        break;
                    }
                }
            }
            //add map to the list
            aaaaa.push_front(bbbb);
        }
    } catch (const std::invalid_argument &e) {
        // do stuff with exception...
        cout << "Cannot open input file.\n";
    }

    //print the list
    //printTheList(aaaaa);

    file.close();
    return aaaaa;
}

size_t parsing_map :: split(const std::string &txt, std::vector<std::string> &strs, char ch) {

    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}

bool parsing_map :: startsWith (string line, string charsStartWith) {
    if(line.length() < charsStartWith.length())
        return false;
    return (line.compare(0, charsStartWith.length(), charsStartWith) == 0);
}

void parsing_map :: printTheList (list<map<string, string>> aaaaa) {
    while ( aaaaa.size() != 0) {
        map<string, string> bbbb;
        bbbb = aaaaa.front();
        aaaaa.pop_front();
        for (auto const& x : bbbb)
        {
            std::cout << x.first  // string (key)
                      << ':'
                      << x.second + "\n" // string's value
                      << std::endl;
        }
    }
}

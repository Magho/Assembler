//
// Created by HP on 28-Apr-18.
//

#include "parsing.h"
#include <fstream>
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
#include "Line.h"

list<Line> parsing :: parisngFunction (string path) {

    ifstream file;
    // path --> "/home/magho/workspaceC++/Assembler/passOne/test.txt"
    file.open(path, ios::in);

    list<Line> aaaaa;
    vector<string> string1;
    std::string str;

    try {

        while (std::getline(file, str)) {

            Line bbbb;

            //transfer to string to lower case
            std::transform(str.begin(), str.end(), str.begin(), ::tolower);

            //check if comment line
            if (startsWith(str, ".")) {

                bbbb.isComment = true;
                bbbb.setcomment(str);

            } else if (str.size() == 0) {
                bbbb.isMoreThanFourWords = true;
            } else {

                split(str, string1, ' ');
                for (int i = 0; i < string1.size(); i++) {

                    if (startsWith(string1[i], ".")) {
                        string str123 = "";
                        for (int j = i; j < string1.size(); j++) {
                            str123 = str123 + string1[j] + " ";
                        }
                        //remove the extra space at the end
                        str123 = str123.substr(0, str123.size() - 1);
                        bbbb.setcomment(str123);

                        break;
                    }
                     else if (i == 0) {
                        char x = string1[i][0];
                        if ((int(x) >= 65 && int(x) <= 90 )| (int(x) <= 122 && int(x) >= 97)) {
                            bbbb.setWord1(string1[i]);
                        } else {
                            bbbb.isMoreThanFourWords = true;
                            break;
                        }
                    }
                    else if (i == 1)
                        bbbb.setWord2(string1[i]);
                    else if (i == 2)
                        bbbb.setWord3(string1[i]);
                    else {
                        bbbb.isMoreThanFourWords = true;
                        break;
                    }
                }
            }
            //add row to the list
            aaaaa.push_front(bbbb);
        }

    } catch (const std::invalid_argument &e) {
        // do stuff with exception...
        cout << "Cannot open input file.\n";
    }
    file.close();
    return aaaaa;
}

size_t parsing :: split(const std::string &txt, std::vector<std::string> &strs, char ch) {

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

bool parsing :: startsWith (string line, string charsStartWith) {
    if(line.length() < charsStartWith.length())
        return false;
    return (line.compare(0, charsStartWith.length(), charsStartWith) == 0);
}

void parsing :: printTheList (list<Line> aaaaa) {
    while ( aaaaa.size() != 0) {
        Line bbbb;
        bbbb = aaaaa.front();
        aaaaa.pop_front();

        cout << "comment is " + bbbb.getcomment();
        cout << "word1" + bbbb.getWord1();
        cout << "word2" + bbbb.getWord2();
        cout << "word3" + bbbb.getWord3();

        //make it "true or false" rather than "0 or 1"
        std::cout << std::boolalpha;
        cout << "is comment" + bbbb.isComment;

        std::cout << std::boolalpha;
        cout << "is more than four words" + bbbb.isMoreThanFourWords;

    }

}


#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <list>
#include <fstream>

using namespace std ;
#include "Row.h"



//
// Created by HP on 23-Apr-18.
//


void Pass1();
void fillFileList();
bool startsWith(string line, string charsStartWith);
size_t split(const std::string &txt, std::vector<std::string> &strs, char ch);
bool checkIfContainSymbol (string symbol);
bool checkIfSymbolDefinedBefore(string symbol);
bool searchOPTABForOPCODE (string OPCODE);
vector <Row> listFile ;
map<string,int> symTab;

int main() {

    ifstream file;
    file.open("/home/magho/workspaceC++/Assembler/passOne/test.txt", ios::in);

    if(!file) {
        cout << "Cannot open input file.\n";
        return 1;
    }

    list<map<string, string>> aaaaa;
    vector <string> string1;
    std::string str;
    while (std::getline(file, str)) {

        map<string, string> bbbb;

        //transfer to string to lower case
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);

        //check if comment line
        if (startsWith(str,".")) {

            bbbb.insert(std::pair<string, string>("commentonly", "true"));
            bbbb.insert(std::pair<string, string>("comment", str));

        } else {

            split(str, string1, ' ');
/*            //print 1
            for (int i = 0; i < string1.size(); i++) {
                cout << string1[i] + "     ";
            }
            cout << "\n";*/
            for (int i = 0; i < string1.size(); i++) {

                if (startsWith(string1[i],".")) {
                    string str123 = "";
                    for (int j = i; j < string1.size(); j++) {
                        str123 = str123 + string1[j] + " ";
                    }
                    //remove the extra space at the end
                    str123 = str123.substr(0,str123.size()-1);
                    bbbb.insert(std::pair<string, string>("comment", str123));

                    break;
                } else if (i == 0)
                    bbbb.insert(std::pair<string, string>("word1", string1[i]));
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
    file.close();
/*    //print 2
    while ( aaaaa.size() != 0) {
        map<string, string> bbbb;
        bbbb = aaaaa.front();
        aaaaa.pop_front();
        for (auto const& x : bbbb)
        {
            std::cout << x.first  // string (key)
                      << ':'
                      << x.second + "\n" // string's value
                      << std::endl  ;
        }
    }*/

//    Row r;
//
//r.setcomment("temona");
//r.setAddress(5);
//r.setLabel("h");
//r.setop_code("opcode");
//r.setOperand("operand");
    //cout << r.getcomment()<<endl <<r.getAddress()<<endl<<r.getLabel() <<endl<<r.getop_code()<<endl<<r.getOperand();



//        vector <Row> listFile ;
//        listFile.push_back(r);
    //  cout << listFile.at(0).getOperand();
    //cout <<"aayy";
    fillFileList();
    Pass1();
    cout << "test";

    return 0;
}
void fillFileList(){
    Row r ;
    r.setLabel("prog");
    r.setop_code("start");
    r.setOperand("1000");
    listFile.push_back(r);

    r.setLabel("loop");
    r.setop_code("lda");
    r.setOperand("x");
    listFile.push_back(r);

    r.setop_code("byte");
    r.setOperand("c'rita'");
    listFile.push_back(r);

    r.setop_code("comp");
    r.setOperand("x");
    listFile.push_back(r);
}
void Pass1 () {

    int LOCCTR;

    // TODO read first input line

    Row row =listFile.at(0);
    if (row.getop_code().compare("start") == 0) {
        // TODO save value of [OPERAND] as starting address
        // TODO initialize [LOCCTR] to stating address
        // TODO write line to intermediate file
        // TODO read next input line
        LOCCTR = atoi( row.getOperand().c_str() );
        row.setAddress(LOCCTR);
        row = listFile.at(1);
    } else {
        LOCCTR=0;
        row.setAddress(0);
    }
    while (row.getop_code().compare("END") != 0){
        //is not a comment line
        if (!row.isComment) {
            if (row.getLabel().compare("null")!=0) {
                bool found = checkIfSymbolDefinedBefore(row.getLabel());//return true if exist
                if (found) {
                    // TODO set error flag (duplicate symbol)
                    row.hasDuplicateError=true;
                } else {
                    // TODO insert (LABEL,LOCCTR) into SYMTAB
                }
            }

            //search OPTAB for OPCODE
            if (searchOPTABForOPCODE(row.getop_code())) {

                // increase location counter by length of the line (assume all 3)
                LOCCTR = LOCCTR + 3;

            } else if (row.getop_code().compare("word") == 0) {

                // increase location counter by length of the word  (3 bytes)
                LOCCTR = LOCCTR + 3;

            } else if (row.getop_code().compare("resw") == 0) {

                // TODO add 3 * #[OPPERAND] to LOCCTR

            } else if (row.getop_code().compare("resb") == 0) {

                // TODO add #[OPERAND] to LOCCTR//7welha l hex
                LOCCTR= atoi( row.getOperand().c_str() );
            } else if (row.getop_code().compare("byte") == 0){
                cout<<"vv" << row.getOperand().at(0);
                // TODO find the length of constant in bytes
                // TODO length to LOCCTR

            } else {

                // TODO set error flag (invalid OPCODE)

            }
        }

        // TODO write line to intermediate file
        // TODO read next input line
    }

    // TODO write last line to intermediate file
    // TODO save (LOCCTR - Starting address) as program length
}

bool startsWith (string line, string charsStartWith) {
    if(line.length() < charsStartWith.length())
        return false;
    return (line.compare(0, charsStartWith.length(), charsStartWith) == 0);
}

// TODO implement check if label is symbol
bool checkIfContainSymbol (string symbol) {
    // TODO set symbol to the found one

    return false;
}

// TODO implement checkIfSymbolDefinedBefore
bool checkIfSymbolDefinedBefore (string symbol) {
    return false;
}

// TODO implement searchOPTABForOPCODE
bool searchOPTABForOPCODE (string OPCODE) {
    return false;
}

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch) {

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

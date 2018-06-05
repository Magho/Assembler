//
// Created by magho on 05/06/18.
//

#ifndef PASSONE_PASS2_H
#define PASSONE_PASS2_H


#include <string>
#include <vector>
#include "Row.h"

using namespace std ;

class Pass2{

private:

public:

    void pass2Algoritm(vector <Row> listFile);
    bool startsWith (string line, string charsStartWith);
    bool endWith (string line, string charsStartWith);
    int formatType (string opcode);
    int calcPC (int currentAddress, int format);

};

#endif //PASSONE_PASS2_H

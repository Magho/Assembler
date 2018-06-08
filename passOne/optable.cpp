//
// Created by HP on 24-Apr-18.
//

#include "optable.h"
void optable :: setTable (void){

    opTable.insert(pair<string, string>("add", "18"));

    opTable.insert(pair<string, string>("addf", "58"));

    opTable.insert(pair<string, string>("addr", "90"));

    opTable.insert(pair<string, string>("and", "40"));

    opTable.insert(pair<string, string>("clear","B4"));

    opTable.insert(pair<string, string>("comp", "28"));

    opTable.insert(pair<string, string>("compf", "88"));

    opTable.insert(pair<string, string>("compr", "a0"));

    opTable.insert(pair<string, string>("div", "24"));

    opTable.insert(pair<string, string>("divf", "64"));

    opTable.insert(pair<string, string>("divr", "9c"));

    opTable.insert(pair<string, string>("fix", "c4"));

    opTable.insert(pair<string, string>("float", "c0"));

    opTable.insert(pair<string, string>("hio", "f4"));

    opTable.insert(pair<string, string>("j", "3c"));

    opTable.insert(pair<string, string>("jeq", "30"));

    opTable.insert(pair<string, string>("jgt", "34"));

    opTable.insert(pair<string, string>("jlt", "38"));

    opTable.insert(pair<string, string>("jsub", "48"));

    opTable.insert(pair<string, string>("lda", "00"));

    opTable.insert(pair<string, string>("ldb", "68"));

    opTable.insert(pair<string, string>("ldch", "50"));

    opTable.insert(pair<string, string>("ldf", "70"));

    opTable.insert(pair<string, string>("ldl", "08"));

    opTable.insert(pair<string, string>("lds", "6c"));

    opTable.insert(pair<string, string>("ldt", "74"));

    opTable.insert(pair<string, string>("ldx", "04"));

    opTable.insert(pair<string, string>("lps", "d0"));

    opTable.insert(pair<string, string>("mul", "20"));

    opTable.insert(pair<string, string>("mulf", "60"));

    opTable.insert(pair<string, string>("mulr", "98"));

    opTable.insert(pair<string, string>("norm", "c8"));

    opTable.insert(pair<string, string>("or", "44"));

    opTable.insert(pair<string, string>("rd", "d8"));

    opTable.insert(pair<string, string>("rmo", "ac"));

    opTable.insert(pair<string, string>("rsub", "4c"));

    opTable.insert(pair<string, string>("shiftl", "a4"));

    opTable.insert(pair<string, string>("shiftr", "a8"));

    opTable.insert(pair<string, string>("sio", "f0"));

    opTable.insert(pair<string, string>("ssk", "ec"));

    opTable.insert(pair<string, string>("sta", "0c"));

    opTable.insert(pair<string, string>("stb", "78"));

    opTable.insert(pair<string, string>("stch", "54"));

    opTable.insert(pair<string, string>("stf", "80"));

    opTable.insert(pair<string, string>("sti", "d4"));

    opTable.insert(pair<string, string>("stl", "14"));

    opTable.insert(pair<string, string>("sts", "7c"));

    opTable.insert(pair<string, string>("stsw", "e8"));

    opTable.insert(pair<string, string>("stt", "84"));

    opTable.insert(pair<string, string>("stx", "10"));

    opTable.insert(pair<string, string>("sub", "1c"));

    opTable.insert(pair<string, string>("subf", "5c"));

    opTable.insert(pair<string, string>("subr", "94"));

    opTable.insert(pair<string, string>("svc", "b0"));

    opTable.insert(pair<string, string>("td", "e0"));

    opTable.insert(pair<string, string>("tio", "f8"));

    opTable.insert(pair<string, string>("tix", "2c"));

    opTable.insert(pair<string, string>("tixr", "b8"));

    opTable.insert(pair<string, string>("wd", "dc"));

    opTable.insert(pair<string, string>("resw", "null"));
    opTable.insert(pair<string, string>("resb", "null"));
    opTable.insert(pair<string, string>("word", "null"));
    opTable.insert(pair<string, string>("byte", "null"));
    opTable.insert(pair<string, string>("end", "null"));
    opTable.insert(pair<string, string>("start", "null"));
    opTable.insert(pair<string, string>("equ", "nothing"));
    opTable.insert(pair<string, string>("org", "nothing"));
}

string optable::getOptable(string str){
    return opTable[str];
}

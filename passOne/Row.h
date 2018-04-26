//
// Created by HP on 24-Apr-18.
//

#ifndef ASSEMBLER_ROW_H
#define ASSEMBLER_ROW_H
#include <string>
#include <cstring>
using namespace std ;

class Row{

private: string Address;
    string label;
    string op_code;
    string operand;
    string errorMessage;

    // setOperand (string setOperand);
    string comment;
public:
    bool hasDuplicateError=false;
    bool isComment=false;
    bool hasInvalidOPCODE=false;
    void setLabel(string );
    string getLabel ();
    void setOperand (string);
    void setop_code (string );
    string getOperand (void);
    void setcomment (string );
    string  getcomment (void);
    void setAddress (string );
    string  getAddress (void) ;
    string getop_code(void);
    string getErrorMessage(void);
    void setErrorMessage(string);


};



#endif //ASSEMBLER_ROW_H

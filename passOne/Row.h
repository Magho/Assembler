//
// Created by HP on 24-Apr-18.
//

#ifndef ASSEMBLER_ROW_H
#define ASSEMBLER_ROW_H
#include <string>
using namespace std ;

class Row{

private: string Address;
    string label;
    string op_code;
    string operand;
    string error;


    // setOperand (string setOperand);
    string comment;
public:
    string errorMessge;
    bool hasError=false;
    bool isComment=false;
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
    void setErrorMessage1(string);
    string getErrorMessage1(void);
    void setError(string);
    string getError(void);


};



#endif //ASSEMBLER_ROW_H

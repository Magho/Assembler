//
// Created by HP on 23-Apr-18.
//

#include <cstring>
#include <string>

using namespace std;

class Row{

private: int Address;
    string label;
    string op_code;
    string operand;

    // setOperand (string setOperand);
    string comment;
public:
    bool hasDuplicateError=false;
    bool isComment;
    void setLabel(string );
    string getLabel ();
    void setOperand (string);
    void setop_code (string );
    string getOperand (void);
    void setcomment (string );
    string  getcomment (void);
    void setAddress (int );
    int  getAddress (void) ;
    string getop_code(void);
};




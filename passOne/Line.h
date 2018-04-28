//
// Created by HP on 28-Apr-18.
//

#ifndef PASSONE_LINE_H
#define PASSONE_LINE_H

#include <string>
#include <cstring>
using namespace std ;

class Line {
 private:

        string comment="null";
        string word1="null";
        string word2="null";
        string word3="null";

    public:

        bool isComment= false;
        bool isMoreThanFourWords;
        int NumofwORD=0 ;
        void setcomment (string );
        string  getcomment (void);

        void setWord1 (string );
        string  getWord1 (void);

        void setWord2 (string );
        string  getWord2 (void);

        void setWord3 (string );
        string  getWord3 (void);

};


#endif //PASSONE_LINE_H

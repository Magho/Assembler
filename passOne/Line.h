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

        string comment;
        string word1;
        string word2;
        string word3;

    public:

        bool isComment;
        bool isMoreThanFourWords;

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

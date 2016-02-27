#ifndef LITERAL_H_
#define LITERAL_H_

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#define SIGN_MASK 0x1

class Literal {
    public:
        Literal(const int v);
        bool GetSign() {return SIGN_MASK & _v;} // 0: pos 1:neg
        bool IsPos() {return !this->GetSign();}
        bool IsNeg() {return this->GetSign();}

        unsigned int GetVariable() {return _v >> 1;}

        void Complement() {_v = SIGN_MASK ^ _v;}

        string GetString();
    private:
        unsigned int _v;
};

#endif

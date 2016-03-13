#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Literal;

class Variable {
    public:
        Variable(const unsigned int v);

        Literal *GetPosLit() {return _posLit;}
        Literal *GetNegLit() {return _negLit;}

        bool IsAssigned() {return _isAssigned;}
        bool GetAssignedValue() {return _assignedValue;}

        unsigned int GetNumeric() {return _v;}
        string GetString();
    protected:
        unsigned int _v;
        Literal *_posLit;
        Literal *_negLit;

        bool _isAssigned;
        bool _assignedValue;
};

#endif

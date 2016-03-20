#ifndef CLAUSE_H_
#define CLAUSE_H_

#include <vector>
#include <sstream>
#include <bitset>
#include <assert.h>
#include <cstdarg>

#include "Literal.h"

using namespace std;

template <class CType>
class Clause {
    public:
        Clause() {};

        unsigned int GetSize() {return _literals.size();}
        void Insert(CType* v) {_literals.push_back(v);}

        CType* Get(unsigned int idx) {
            if (idx < _literals.size()) {
                return _literals[idx];
            } else {
                assert(0);
            }
        }

        virtual string GetString();
    protected:
        vector<CType*> _literals;
};

template <class CType>
string Clause<CType>::GetString() {
    string s;
    for (unsigned int i = 0 ; i < _literals.size() ; i++) {
        s += _literals[i]->GetString();
        s += ' ';
    }
    return s;
}

#endif

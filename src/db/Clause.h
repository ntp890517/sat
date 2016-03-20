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
        Clause(CType *&lit1);
        Clause(CType *&lit1, CType *&lit2);
        Clause(CType *&lit1, CType *&lit2, CType *&lit3);

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
Clause<CType>::Clause(CType *&lit1) {
    _literals.push_back(lit1);
}

template <class CType>
Clause<CType>::Clause(CType *&lit1, CType *&lit2) {
    _literals.push_back(lit1);
    _literals.push_back(lit2);
}

template <class CType>
Clause<CType>::Clause(CType *&lit1, CType *&lit2, CType *&lit3) {
    _literals.push_back(lit1);
    _literals.push_back(lit2);
    _literals.push_back(lit3);
}

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

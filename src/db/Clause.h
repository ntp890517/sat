#ifndef CLAUSE_H_
#define CLAUSE_H_

#include <vector>
#include <sstream>
#include <bitset>
#include <assert.h>
#include <cstdarg>
#include <typeinfo>

#include "Literal.h"
#include "../ut/ut.h"

using namespace std;

template <class CType>
class Clause {
    public:
        Clause() {
            if (typeid(CType) != typeid(Literal)) {
                PROGERROR() << "Clause is for Literal and its derived class."
                            << endl;
                assert(0);
            }
        };

        unsigned int GetSize() {return _literals.size();}
        void Insert(CType* v) {_literals.push_back(static_cast<Literal*>(v));}

        bool IsSat();

        CType* Get(unsigned int idx) {
            if (idx < _literals.size()) {
                return static_cast<CType*>(_literals[idx]);
            } else {
                assert(0);
            }
        }

        virtual string GetString();
    protected:
        vector<Literal*> _literals;
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

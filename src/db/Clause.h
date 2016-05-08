#ifndef CLAUSE_H_
#define CLAUSE_H_

#include <vector>
#include <list>
#include <sstream>
#include <bitset>
#include <assert.h>
#include <cstdarg>
#include <typeinfo>
#include <algorithm>

#include "Literal.h"
#include "../ut/ut.h"

using namespace std;

class Clause {
    public:
        unsigned int GetSize() {return _literals.size();}
        void Insert(Literal* v) {_literals.push_back(v);}

        virtual bool IsSat();
        virtual bool IsUnsat();

        Literal* Get(unsigned int idx) {
            if (idx < _literals.size()) {
                return _literals[idx];
            } else {
                assert(0);
            }
        }
        void Unique();

        virtual string GetString();
    protected:
        vector<Literal*> _literals;
};

#endif

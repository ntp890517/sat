#ifndef CLAUSE_H_
#define CLAUSE_H_

#include <vector>
#include <list>
#include <sstream>
#include <bitset>
#include <assert.h>
#include <cstdarg>
#include <typeinfo>

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

        virtual string GetString();

        void PushChildImpNode(Literal* lit) {_impNodes.push_back(lit);}

        void SetFlag1() {_flag1 = true;}
        void UnsetFlag1() {_flag1 = false;}
        bool IsFlag1() {return _flag1;}

        void SetFlag2() {_flag2 = true;}
        void UnsetFlag2() {_flag2 = false;}
        bool IsFlag2() {return _flag2;}
    protected:
        vector<Literal*> _literals;

        list<Literal*> _impNodes;

        bool _flag1;
        bool _flag2;
};
#endif

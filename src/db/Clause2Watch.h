#ifndef CLAUSE_2_WATCH_H_
#define CLAUSE_2_WATCH_H_

#include "Clause.h"

class Clause2Watch : public Clause {
        void Setup2Watch();
        void Update2Watch(Literal* literalToBeUpdated);

        bool IsUnsat();

        Literal* GetWatch1() {return _literals[_watch1];}
        Literal* GetWatch2() {return _literals[_watch2];}
    protected:
        bool IsBothUnsat() {return GetWatch1()->IsUnsat() &&
                                   GetWatch2()->IsUnsat();}
        unsigned int FindNextUnassignedLiteral(unsigned int start);
    protected:
        unsigned int _watch1;
        unsigned int _watch2;
};

#endif

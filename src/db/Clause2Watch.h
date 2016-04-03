#ifndef CLAUSE_2_WATCH_H_
#define CLAUSE_2_WATCH_H_

#include "Clause.h"

class Clause2Watch : public Clause {
    public:
        void Setup2Watch();
        void Update2Watch(Literal* literalToBeUpdated);

        Literal* GetWatch1() {return _literals[_watchIdx1];}
        Literal* GetWatch2() {return _literals[_watchIdx2];}
    protected:
        bool IsBothUnsat() {return GetWatch1()->IsUnsat() &&
                                   GetWatch2()->IsUnsat();}
        unsigned int GetNextWatchIdx(unsigned int startIdx);
        bool IsNeedUpdate(Literal* literalToBeUpdated);
    protected:
        unsigned int _watchIdx1;
        unsigned int _watchIdx2;
};

#endif

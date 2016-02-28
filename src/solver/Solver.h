#ifndef SOLVER_H_
#define SOLVER_H_

#include <string>

#include "../db/Cnf.h"

class Solver {
    public:
        enum Result {
            UNDEF = -1,
            UNSAT,
            SAT,
        };

        Solver():_result(UNDEF), _debug(false) {};

        virtual void ReadCnf(const string cnfName) = 0;
        virtual void Preprocess() = 0;
        virtual void Solve() = 0;
        virtual string GetAssignment() = 0;

        bool IsSat() {return _result == SAT;}
        bool IsUnsat() {return _result == UNSAT;}
        bool IsUndef() {return _result == UNDEF;}
        Result GetResult() {return _result;}

        void SetDebug() {_debug = true;}
        void UnsetDebug() {_debug = false;}
        bool IsDebug() {return _debug;}
    protected:
        Result _result;
        bool _debug;
};
#endif

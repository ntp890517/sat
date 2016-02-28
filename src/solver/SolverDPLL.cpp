#include "SolverDPLL.h"

void SolverDPLL::Solve()
{
    _result = Preprocess();

    if (_result != UNDEF) {
        return;
    }
    while(1) {
        Decide();
        while(true) {
            _result = Deduce();
            if (_result == UNDEF) {
                Level backToLevel = Analyze();
                if (backToLevel < 0) {
                    _result = UNSAT;
                    return;
                } else {
                    BackTrack(backToLevel);
                }
            } else if (_result == SAT) {
                return;
            } else {
                break;
            }
        }
    }
}

Solver::Result SolverDPLL::Preprocess()
{
    return Solver::UNDEF;
}

void SolverDPLL::Decide()
{
    ;
}

Solver::Result SolverDPLL::Deduce()
{
    return Solver::UNDEF;
}

Level SolverDPLL::Analyze()
{
    return Solver::UNDEF;
}

void SolverDPLL::BackTrack(Level lv)
{
    ;
}


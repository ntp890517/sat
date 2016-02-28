#ifndef SOLVERDPLL_H_
#define SOLVERDPLL_H_

#include "Solver.h"

typedef unsigned int Level;

class SolverDPLL : public Solver {
    public:
        virtual void Solve();
    private:
        Solver::Result Preprocess();
        void Decide();
        Solver::Result Deduce();
        Level Analyze();
        void BackTrack(Level lv);
};
#endif

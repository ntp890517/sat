#ifndef SOLVER_BRUTE_FORCE_H_
#define SOLVER_BRUTE_FORCE_H_

#include "Solver.h"
#include <sstream>
#include <string>

using namespace std;

class SolverSimulate: public Solver {
    public:
        virtual void ReadCnf(const string cnfName);
        virtual void Solve();
        virtual string GetAssignment();
    private:
        void CheckAssignment();
        void NextAssignment();

        Cnf *_cnf;
        vector<bool> *_assignment;
};
#endif

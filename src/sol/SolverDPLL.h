#ifndef SOLVERDPLL_H_
#define SOLVERDPLL_H_

#include "Solver.h"
#include <iostream>
#include <fstream>
#include "../ut/ut.h"

typedef unsigned int Level;

class SolverDPLL : public Solver {
    public:
        virtual void ReadCnf(const string cnfName);
        virtual void Solve();
        virtual string GetAssignment();

        unsigned int GetNumOfClauses() {return _clauses.size();}
        unsigned int GetNumOfVariables() {return _variables.size() - 1;}

        void Display();
    private:
        void InitVariables(unsigned int);
        Clause* ParseClause(string s);
        Solver::Result Preprocess();
        void Decide();
        Solver::Result Deduce();
        Level Analyze();
        void BackTrack(Level lv);
    private:
        vector<Clause*> _clauses;
        vector<Variable*> _variables;
};
#endif

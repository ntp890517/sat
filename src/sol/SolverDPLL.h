#ifndef SOLVERDPLL_H_
#define SOLVERDPLL_H_

#include "Solver.h"
#include <iostream>
#include <fstream>
#include "../db/Clause2Watch.h"
#include "../db/Literal.h"
#include "../db/Variable.h"
#include "../ut/ut.h"
#include <list>
#include <queue>

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
        Clause2Watch* ParseClause(string s);
        Solver::Result Preprocess();
        Literal* Decide();
        Solver::Result Deduce(Literal*);
        Level Analyze();
        void BackTrack(Level lv);
    private:
        vector<Clause2Watch*> _clauses;
        vector<Variable*> _variables;

        list<vector<pair<Literal*, Clause2Watch*> > > _impGraph;
};
#endif

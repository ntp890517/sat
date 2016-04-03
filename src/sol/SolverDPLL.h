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
#include <vector>
#include <iterator>

typedef unsigned int Level;

using namespace std;

class ImplicationGraph {
    public:
        void AddDecide(Literal* decide) { _decides.push_back(decide); }
        unsigned int GetCurrentLevel() { return _decides.size() - 1; }
    private:
        bool BCP();
        vector<Literal*> _decides;
};

class SolverDPLL : public Solver {
    friend class ImplicationGraph;

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

        ImplicationGraph _impGraph;
};

#endif

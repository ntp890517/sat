#ifndef SOLVERDPLL_H_
#define SOLVERDPLL_H_

#include "Solver.h"

#include <iostream>
#include <fstream>

#include <list>
#include <queue>
#include <vector>
#include <iterator>

#include "../db/db.h"
#include "../ut/ut.h"

typedef unsigned int Level;

using namespace std;

class ClauseDPLL : public Clause2Watch, public ImplicationGraphEdge {
};

class LiteralDPLL : public Literal, public ImplicationGraphNode {
    public:
        LiteralDPLL(Variable *var, const bool sign) : Literal(var, sign) {};
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
        ClauseDPLL* ParseClause(string s);
        //Solver::Result Preprocess();
        //Literal* Decide();
        //Solver::Result Deduce(Literal*);
        //Level Analyze();
        //void BackTrack(Level lv);
    private:
        vector<ClauseDPLL*> _clauses;
        vector<Variable*> _variables;
};

#endif

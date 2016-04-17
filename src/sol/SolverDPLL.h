#ifndef SOLVERDPLL_H_
#define SOLVERDPLL_H_

#include "Solver.h"

#include <iostream>
#include <fstream>

#include <list>
#include <queue>
#include <vector>
#include <iterator>
#include <cctype>

#include "../db/db.h"
#include "../ut/ut.h"

typedef unsigned int Level;

using namespace std;

class LiteralDPLL : public Literal, public ImplicationGraphNode {
    public:
        LiteralDPLL(Variable *var, const bool sign) : Literal(var, sign) {};
        LiteralDPLL* GetComplementLiteral() {
            return static_cast<LiteralDPLL*>(Literal::GetComplementLiteral());
        }
};

class ClauseDPLL : public Clause2Watch, public ImplicationGraphEdge {
    public:
        LiteralDPLL* Deduce(LiteralDPLL* assign) {
            return static_cast<LiteralDPLL*>(Clause2Watch::Deduce(assign));
        }
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
        bool Preprocess();
        bool BCP(LiteralDPLL* assign);
        LiteralDPLL* Decide();
        //Solver::Result Deduce(Literal*);
        unsigned Analyze();
        list<ClauseDPLL*> GetFirstUipCut();
        void BackTrack(unsigned int toLevel);
    private:
        vector<ClauseDPLL*> _clauses;
        vector<Variable*> _variables;
        LiteralDPLL* _uip;

        ImplicationGraph _impGraph;
};

#endif

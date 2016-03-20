#ifndef SOLVER_BRUTE_FORCE_H_
#define SOLVER_BRUTE_FORCE_H_

#include "Solver.h"
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

class SolverSimulate: public Solver {
    public:
        virtual void ReadCnf(const string cnfName);
        virtual void Solve();
        virtual string GetAssignment();
    private:
        bool CheckAssignment();
        bool NextAssignment();

        unsigned int GetNumOfClauses() {return _clauses.size();}
        unsigned int GetNumOfVariables() {return _variables.size() - 1;}

        void InitVariables(const unsigned int nVar);
        Clause<Literal> *ParseClause(string s);
        void Display();

    private:
        vector<Clause<Literal>*> _clauses;
        vector<Variable*> _variables;
};
#endif

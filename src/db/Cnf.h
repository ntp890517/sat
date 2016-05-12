#ifndef CNF_H_
#define CNF_H_

#include <vector>
#include <cassert>

#include "Literal.h"
#include "Variable.h"
#include "Clause.h"

using namespace std;

class Cnf {
    public:
        Variable* GetVariable(unsigned v) {return _variables[v];}
        Clause* GetClause(unsigned idx) {return _clauses[idx];}
        Literal* GetLiteral(int lit) {
            if (lit > 0) {
                _variables[lit]->GetPosLit();
            } else if (lit < 0) {
                _variables[-lit]->GetNegLit();
            } else {
                assert(0);
            }
        }

        void PushVariable(Variable* v) {_variables.push_back(v);}
        void PushClause(Clause* c) {_clauses.push_back(c);}

        unsigned GetVariablesSize() {return _variables.size() - 1;}
        unsigned GetClausesSize() {return _clauses.size();}

        void Dump();
    protected:
        vector<Clause*> _clauses;
        vector<Variable*> _variables;
};

#endif


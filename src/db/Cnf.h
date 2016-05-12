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
    protected:
        vector<Clause*> _clauses;
        vector<Variable*> _variables;
};

#endif


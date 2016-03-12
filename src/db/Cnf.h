#ifndef CNF_H_
#define CNF_H_

#include <vector>
#include <string>

#include "Clause.h"
#include "Variable.h"
#include "Literal.h"

using namespace std;

class Cnf {
    public:
        Cnf(const string cnfName);

        unsigned int GetNumOfVariable() {return _variable.size() - 1;}
        unsigned int GetNumOfClause() {return _clauses.size();}

        Clause<Literal> *GetClause(unsigned int idx) {return _clauses[idx];}

        void Display();
    private:
        void InitVariable(const unsigned int nVar);
        Clause<Literal> *ParseClause(string s);
        vector<Clause<Literal>*> _clauses;
        vector<Variable*> _variable;
};

#endif

#ifndef CNF_H_
#define CNF_H_

#include <vector>
#include <string>

#include "Clause.h"
#include "Literal.h"

using namespace std;

class Cnf {
    public:
        Cnf(const string cnfName);

        unsigned int GetNumOfVariable() {return _nVariable;}
        unsigned int GetNumOfClause() {return _nClause;}

        Clause* GetClause(unsigned int idx) {return _clauses[idx];}
    private:
        vector<Clause*> _clauses;
        unsigned int _nVariable;
        unsigned int _nClause;
};

#endif

#ifndef LITERAL_H_
#define LITERAL_H_

#include <iostream>
#include <sstream>
#include <string>
#include <list>

#include "Variable.h"
#include "Clause.h"

using namespace std;

#define SIGN_MASK 0x1

class Literal {
    public:
        Literal(Variable *var, const bool sign) : _var(var), _sign(sign) {}

        bool GetSign() {return _sign;}
        bool IsPos() {return _sign;}
        bool IsNeg() {return !_sign;}

        bool IsSat();
        bool IsUnsat();

        Variable *GetVariable() {return _var;}

        string GetString();
        int GetNumeric();

        void AddClause(Clause* clause) {_clauses.push_back(clause);}
        bool HasNoRelatedClauses() {return _clauses.empty();}
    protected:
        Variable *_var;
        bool      _sign;
        list<Clause*> _clauses;
};

#endif

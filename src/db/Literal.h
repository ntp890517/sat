#ifndef LITERAL_H_
#define LITERAL_H_

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <iterator>

#include "Variable.h"

using namespace std;

#define SIGN_MASK 0x1

class Clause;

class Literal {
    public:
        Literal(Variable *var, const bool sign) : _var(var), _sign(sign) {}

        bool GetSign() {return _sign;}
        bool IsPos() {return _sign;}
        bool IsNeg() {return !_sign;}

        bool IsSat();
        bool IsUnsat();

        Literal* GetComplementLiteral() {return (this->IsPos()? this->GetVariable()->GetNegLit() : this->GetVariable()->GetPosLit());}

        Variable *GetVariable() {return _var;}

        string GetString();
        int GetNumeric();

        void AddClause(Clause* clause) {_clauses.push_back(clause);}
        void RemoveClause(Clause* clause) {_clauses.remove(clause);}
        void ReplaceClause(Clause* from, Clause* to);
        bool HasNoRelatedClauses() {return _clauses.empty();}

        void SetupClausesIt() {_cit = _clauses.begin();}
        Clause* GetClause() {return (*_cit);}
        bool IsClausesEnd() {return (_cit == _clauses.end());}
        void NextClause() {_cit++;}
    protected:
        Variable *_var;
        bool      _sign;
        list<Clause*>::iterator _cit;
        list<Clause*> _clauses;
};

#endif

#ifndef LITERAL_DP_H_
#define LITERAL_DP_H_

#include "Literal.h"
#include "VariableDP.h"
#include "Clause2Watch.h"

class LiteralDP : public Literal {
    public:
        LiteralDP(VariableDP *var, const bool sign) : Literal(var, sign) {}

        void AddClause(Clause2Watch* clause) {_clauses.push_back(clause);}

        bool HasNoRelatedClauses() {return _clauses.empty();}
        
        vector<Clause2Watch*>::iterator GetClausesBegin() {
            return _clauses.begin();}
        vector<Clause2Watch*>::iterator GetClausesEnd() {
            return _clauses.end();}
    protected:
        vector<Clause2Watch*> _clauses;
};

#endif

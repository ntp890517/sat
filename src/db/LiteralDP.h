#ifndef LITERAL_DP_H_
#define LITERAL_DP_H_

#include "Literal.h"
#include "Clause2Watch.h"

class LiteralDP : public Literal {
    public:
        void AddClause(Clause* clause) {_clauses.push_back(clause);}
    protected:
        vector<Clause*> _clauses;
};

#endif

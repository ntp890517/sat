#ifndef LITERAL_H_
#define LITERAL_H_

#include <iostream>
#include <sstream>
#include <string>
#include <list>

#include "Variable.h"

using namespace std;

#define SIGN_MASK 0x1

class Clause;
class ImplicationGraph;

class Literal {
    friend ImplicationGraph;

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
        bool HasNoRelatedClauses() {return _clauses.empty();}

        void PushImpOutEdge(Clause* cl) {_impOutEdges.push_back(cl);}
        void PushImpInEdge(Clause* cl) {_impInEdges.push_back(cl);}

        void SetFlag1() {_flag1 = true;}
        void UnsetFlag1() {_flag1 = false;}
        bool IsFlag1() {return _flag1;}

        void SetFlag2() {_flag2 = true;}
        void UnsetFlag2() {_flag2 = false;}
        bool IsFlag2() {return _flag2;}
    protected:
        Variable *_var;
        bool      _sign;
        list<Clause*> _clauses;

        list<Clause*> _impOutEdges;
        list<Clause*> _impInEdges;

        bool _flag1;
        bool _flag2;
};

#endif

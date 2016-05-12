#ifndef LITERAL_DPLL_H_
#define LITERAL_DPLL_H_

#include <vector>
#include <cassert>

#include "Literal.h"
#include "../db/ImplicationGraph.h"

using namespace std;

class LiteralDPLL : public Literal, public ImplicationGraphNode {
    public:
        LiteralDPLL(Variable *var, const bool sign) : Literal(var, sign) {};
        LiteralDPLL* GetComplementLiteral() {
            return static_cast<LiteralDPLL*>(Literal::GetComplementLiteral());
        }
};
#endif

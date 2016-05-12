#ifndef CLAUSE_DPLL_H_
#define CLAUSE_DPLL_H_

#include <vector>
#include <cassert>

#include "Clause2Watch.h"
#include "LiteralDPLL.h"
#include "../db/ImplicationGraph.h"

using namespace std;

class ClauseDPLL : public Clause2Watch, public ImplicationGraphEdge {
    public:
        LiteralDPLL* Deduce(LiteralDPLL* assign) {
            return static_cast<LiteralDPLL*>(Clause2Watch::Deduce(assign));
        }
};
#endif


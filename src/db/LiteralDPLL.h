#ifndef LITERAL_DPLL_H_
#define LITERAL_DPLL_H_

#include "Literal.h"

using namespace std;

class LiteralDPLL : public Literal {
    public:
        Literal(const int v);

        bool IsAssigned() {return _isAssigned;}

    protected:
        bool _isAssigned;
};

#endif

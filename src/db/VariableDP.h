#ifndef VARIABLE_DP_H_
#define VARIABLE_DP_H_

#include "Variable.h"

class LiteralDP;

class VariableDP : public Variable {
    public:
        VariableDP(const unsigned int v);

        LiteralDP* GetPosLit() {return reinterpret_cast<LiteralDP*>(_posLit);}
        LiteralDP* GetNegLit() {return reinterpret_cast<LiteralDP*>(_negLit);}
};

#endif

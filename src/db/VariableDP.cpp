#include "VariableDP.h"
#include "LiteralDP.h"

VariableDP::VariableDP(const unsigned int v) : Variable() {
    _v = v;
    _posLit = new LiteralDP(this, true);
    _negLit = new LiteralDP(this, false);
}

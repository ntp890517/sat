#include "Variable.h"
#include "Literal.h"

using namespace std;

Variable::Variable() : _isAssigned(false) {
}

Variable::Variable(const unsigned int v) : _isAssigned(false) {
    _v = v;
    _posLit = new Literal(this, true);
    _negLit = new Literal(this, false);
}

string Variable::GetString() 
{
    stringstream ss;
    ss << _v;
    return ss.str();
}

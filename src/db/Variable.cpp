#include "Variable.h"
#include "Literal.h"

using namespace std;

Variable::Variable(const unsigned int v) : _v(v), _isAssigned(false)
{
    _posLit = new Literal(this, true);
    _negLit = new Literal(this, false);
}

string Variable::GetString() 
{
    stringstream ss;
    ss << _v;
    return ss.str();
}

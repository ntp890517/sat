#include "Variable.h"
#include "Literal.h"

using namespace std;

Variable::Variable(const unsigned int v) : _isAssigned(false) {
    _v = v;
}

string Variable::GetString() 
{
    stringstream ss;
    ss << _v;
    return ss.str();
}

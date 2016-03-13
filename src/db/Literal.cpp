#include "Literal.h"

using namespace std;

string Literal::GetString() {
    stringstream ss;
    ss << (IsPos()? "":"-") << GetVariable()->GetString();
    return ss.str();
}

int Literal::GetNumeric() {
    return (IsPos()? GetVariable()->GetNumeric() : 
                     -GetVariable()->GetNumeric());
}

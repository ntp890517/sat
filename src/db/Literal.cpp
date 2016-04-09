#include "Literal.h"

using namespace std;

bool Literal::IsSat() {
    if (! _var->IsAssigned()) {
        return false;
    } else {
        return (_sign == _var->GetAssignedValue());
    }
}

bool Literal::IsUnsat() {
    if (! _var->IsAssigned()) {
        return false;
    } else {
        return (_sign != _var->GetAssignedValue());
    }
}

string Literal::GetString() {
    stringstream ss;
    ss << (IsPos()? "":"-") << GetVariable()->GetString();
    return ss.str();
}

int Literal::GetNumeric() {
    return (IsPos()? GetVariable()->GetNumeric() : 
                     -GetVariable()->GetNumeric());
}

void Literal::ReplaceClause(Clause* from, Clause* to) {
    _clauses.remove(from);
    _clauses.push_back(to);
}

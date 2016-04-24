#include <iostream>
#include <sstream>

#include "Clause.h"

static bool CmpDecreasLiteral(Literal* l1, Literal* l2) {
    return (l1->GetNumeric() < l2->GetNumeric());
}

static bool CmpEqual(Literal* l1, Literal* l2) {
    return (l1->GetNumeric() == l2->GetNumeric());
}

string Clause::GetString() {
    string s;
    for (unsigned int i = 0 ; i < _literals.size() ; i++) {
        s += _literals[i]->GetString();

        if (i != _literals.size() - 1) {
            s += ' ';
        }
    }
    return s;
}

bool Clause::IsSat() {
    for (unsigned int i = 0 ; i < _literals.size() ; i++) {
        if (_literals[i]->IsSat()) {
            return true;
        }
    }

    return false;
}

bool Clause::IsUnsat() {
    for (unsigned int i = 0 ; i < _literals.size() ; i++) {
        if (! _literals[i]->IsUnsat()) {
            return false;
        }
    }

    return true;
}

void Clause::Unique() {
    sort(_literals.begin(), _literals.end(), CmpDecreasLiteral);
    vector<Literal*>::iterator it;
    it = unique(_literals.begin(), _literals.end(), CmpEqual);
    _literals.resize(distance(_literals.begin(), it));
}


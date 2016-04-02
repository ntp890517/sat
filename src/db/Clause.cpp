#include <iostream>
#include <sstream>

#include "Clause.h"

string Clause::GetString() {
    string s;
    for (unsigned int i = 0 ; i < _literals.size() ; i++) {
        s += _literals[i]->GetString();
        s += ' ';
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

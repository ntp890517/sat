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

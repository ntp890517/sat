#include <iostream>
#include <sstream>

#include "Clause.h"

Clause::Clause(const string s) {
    int lit;
    istringstream iss(s);

    while(iss >> lit) {
        if (lit == 0) {
            break;
        } else {
            _literals.push_back(new Literal(lit));
        }
    }
}

string Clause::GetString() {
    string s;
    for (unsigned int i = 0 ; i < _literals.size() ; i++) {
        s += _literals[i]->GetString();
        s += ' ';
    }
    return s;
}

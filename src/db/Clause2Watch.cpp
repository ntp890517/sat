#include "Clause2Watch.h"

void Clause2Watch::Setup2Watch() {
    if (_literals.size() == 0) {
        assert(0);
    } else if (_literals.size() == 1) {
        _watch1 = 0;
        _watch2 = 0;
    } else {
        _watch1 = 0;
        _watch2 = 1;
    }
}

void Clause2Watch::Update2Watch(Literal* lit) {
    if (lit != GetWatch1() && lit != GetWatch2()) {
        return;
    } else if (lit == GetWatch1()) {
        _watch1 = FindNextUnassignedLiteral(_watch1);
    } else if (lit == GetWatch2()) {
        _watch2 = FindNextUnassignedLiteral(_watch2);
    }
}

unsigned int Clause2Watch::FindNextUnassignedLiteral(unsigned int start) {
    for (unsigned int i = start + 1 ; i < _literals.size() ; i++) {
        if (! _literals[i]->GetVariable()->IsAssigned()) {
            return i;
        }
    }

    for (unsigned int i = 0 ; i < start ; i++) {
        if (! _literals[i]->GetVariable()->IsAssigned()) {
            return i;
        }
    }

    return start;
}

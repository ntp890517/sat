#include "Clause2Watch.h"

void Clause2Watch::Setup2Watch() {
    if (_literals.size() == 0) {
        assert(0);
    } else if (_literals.size() == 1) {
        _watchIdx1 = 0;
        _watchIdx2 = 0;
    } else {
        _watchIdx1 = 0;
        _watchIdx2 = 1;
    }
}

Literal* Clause2Watch::Update2Watch(Literal* lit) {
    if (! IsNeedUpdate(lit)) {
        return NULL;
    }

    if (lit == GetWatch1()) {
        _watchIdx1 = GetNextWatchIdx(_watchIdx1);
    } else if (lit == GetWatch2()) {
        _watchIdx2 = GetNextWatchIdx(_watchIdx2);
    } else {
        assert(0);
    }

    if (GetWatch1()->IsUnsat() && ! GetWatch2()->IsUnsat()) {
        return GetWatch2();
    } else if (! GetWatch1()->IsUnsat() && GetWatch2()->IsUnsat()) {
        return GetWatch1();
    } else {
        return NULL;
    }
}

bool Clause2Watch::IsNeedUpdate(Literal* lit) {
    if (lit->IsSat()) {
        return false;
    }

    if (lit != GetWatch1() && lit != GetWatch2()) {
        return false;
    }

    if (GetWatch1()->IsSat() || GetWatch2()->IsSat()) {
        return false;
    }

    assert(! GetWatch1()->IsUnsat() || ! GetWatch2()->IsUnsat());

    return true;
}

unsigned int Clause2Watch::GetNextWatchIdx(unsigned int start) {
    for (unsigned int i = 0 ; i < _literals.size() ; i++) {
        if (! _literals[i]->IsUnsat() &&
            _literals[i] != GetWatch1() &&
            _literals[i] != GetWatch2() ) {
            return i;
        }
    }

    return start;
}

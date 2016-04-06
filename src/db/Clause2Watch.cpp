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

void Clause2Watch::Update2Watch(Literal* lit) {
    if (! IsNeedUpdate(lit)) {
        return;
    }

    if (lit == GetWatch1()) {
        _watchIdx1 = GetNextWatchIdx(_watchIdx1);
    } else if (lit == GetWatch2()) {
        _watchIdx2 = GetNextWatchIdx(_watchIdx2);
    } else {
        assert(0);
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
    for (unsigned int i = start + 1 ; i < _literals.size() ; i++) {
        if (! _literals[i]->IsUnsat()) {
            return i;
        }
    }

    for (unsigned int i = 0 ; i < start ; i++) {
        if (! _literals[i]->IsUnsat()) {
            return i;
        }
    }

    return start;
}

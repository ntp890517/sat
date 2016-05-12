#include "CnfBuilder.h"

#include "../db/db.h"
#include "../ut/ut.h"

Cnf* CnfBuilder::GetCnf() {
    if (_isDone) {
        return _cnf;
    } else {
        PROGERROR() << "Cnf building is not finised" << endl;
        assert(0);
        return nullptr;
    }
};

void DpllCnfBuilder::BuildVariableTable(unsigned nrVars) {
    for (unsigned i = 0 ; i < nrVars+1 ; i++) {
        Variable* var;

        var = new Variable(i);
        var->InitLiterals<LiteralDPLL>();
        _cnf->PushVariable(var);
    }
}

void DpllCnfBuilder::BuildClause(string s) {
    istringstream iss(s);
    ClauseDPLL* c = new ClauseDPLL;
    LiteralDPLL *pLit = nullptr;
    int lit;

    while(iss >> lit) {
        if (lit == 0) {
            break;
        } else if (lit > 0) {
            pLit = static_cast<LiteralDPLL*>(_cnf->GetVariable(lit)->GetPosLit());
            c->Insert(pLit);
        } else {
            pLit = static_cast<LiteralDPLL*>(_cnf->GetVariable(-lit)->GetNegLit());
            c->Insert(pLit);
        }
    }

    _cnf->PushClause(c);
}

void DpllCnfBuilder::PostProcess() {
    Setup2WatchLiteral();
    _isDone = true;
}

void DpllCnfBuilder::Setup2WatchLiteral() {
    for (unsigned i = 0 ; i < _cnf->GetClausesSize() ; i++) {
        ClauseDPLL* c = static_cast<ClauseDPLL*>(_cnf->GetClause(i));
        c->Setup2Watch();
        c->GetWatch1()->AddClause(c);
        c->GetWatch2()->AddClause(c);
    }
}

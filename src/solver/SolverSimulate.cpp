#include "SolverSimulate.h"

void SolverSimulate::ReadCnf(const string cnfName) {
    _cnf = new Cnf(cnfName);
    if (IsDebug()) {
        _cnf->Display();
    }
}

string SolverSimulate::GetAssignment() {
    stringstream ss;
    for (unsigned int i = 0 ; i < _assignment->size() - 1 ; i++) {
        ss << (_assignment->at(i)? "":"-") << i+1 << ' ';
    }
    return ss.str();
}

void SolverSimulate::Solve() {
    _assignment = new vector<bool>(_cnf->GetNumOfVariable() + 1);

    while(1) {
        CheckAssignment();
        if (_result == SAT) {
            break;
        }
        NextAssignment();
        if (_assignment->at(_cnf->GetNumOfVariable())) {
            _result = UNSAT;
            break;
        }
    }
}

void SolverSimulate::CheckAssignment() {
    bool result = true;
    Clause<Literal> *cl = NULL;
    Literal *lit = NULL;

    if (IsDebug()) {
        cout << "check ";
        for (unsigned int i = 0 ; i < _cnf->GetNumOfVariable() ; i++) {
            cout << _assignment->at(i);
        }
        cout << endl;
    }

    for (unsigned int i = 0 ; i < _cnf->GetNumOfClause() ; i++) {
        cl = _cnf->GetClause(i);
        if (IsDebug()) {
            cout << cl->GetString();
        }
        bool isSatClause = false;
        for (unsigned int j = 0 ; j < cl->GetSize() ; j++) {
            lit = cl->Get(j);
            if (lit->GetSign() == 
                _assignment->at(lit->GetVariable()->GetNumeric() - 1)) {
                isSatClause = true;
                break;
            }
        }
        if (IsDebug()) {
            cout << (isSatClause? "SAT":"UNSAT") << endl;
        }
        if (!isSatClause) {
            result = false;
            break;
        }
    }

    _result = result ? Solver::SAT : Solver::UNSAT;
}

void SolverSimulate::NextAssignment() {
    for (unsigned int i = 0 ; i < _cnf->GetNumOfVariable() + 1 ; i++) {
        if (_assignment->at(i)) {
            _assignment->at(i) = false;
        } else {
            _assignment->at(i) = true;
            break;
        }
    }
}


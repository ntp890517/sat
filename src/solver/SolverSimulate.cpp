#include "SolverSimulate.h"

void SolverSimulate::ReadCnf(const string cnfName) {
    ifstream fin;
    fin.open(cnfName.c_str());
    unsigned int nVar, nCl;

    string line;
    string buf;
    while(getline(fin, line)) {
        istringstream ss(line);
        if (ss.peek() == 'c') {
            continue;
        } else if (ss.peek() == 'p') {
            ss >> buf >> buf >> nVar >> nCl;
            InitVariables(nVar);
        } else if (ss.peek() == '0') {
            break;
        } else {
            _clauses.push_back(ParseClause(ss.str()));
        }
    }

    fin.close();

    cout << cnfName << " is parsed. "
         << " nVar: " << GetNumOfVariables()
         << " nClause: " << GetNumOfClauses() << endl;
    if (IsDebug()) {
        Display();
    }
}

void SolverSimulate::Solve() {
    for (unsigned int i = 1 ; i < GetNumOfVariables() + 1 ; i++) {
        _variables[i]->Assign(false);
    }

    while(1) {
        if (CheckAssignment()) {
            _result = SAT;
            break;
        }
        if (! NextAssignment()) {
            _result = UNSAT;
            break;
        }
    }
}

string SolverSimulate::GetAssignment() {
    stringstream ss;
    for (unsigned int i = 1 ; i < GetNumOfVariables() + 1 ; i++) {
        ss << (_variables[i]->GetAssignedValue()? "":"-") 
           << i << ' ';
    }
    return ss.str();
}

bool SolverSimulate::CheckAssignment() {
    bool result = true;
    Clause<Literal> *cl = NULL;
    Literal *lit = NULL;

    if (IsDebug()) {
        cout << "check ";
        for (unsigned int i = 1 ; i < GetNumOfVariables() + 1 ; i++) {
            cout << (_variables[i]->GetAssignedValue()? 
                     _variables[i]->GetPosLit()->GetString() :
                     _variables[i]->GetNegLit()->GetString()) << ' ';
        }
        cout << endl;
    }

    for (unsigned int i = 0 ; i < GetNumOfClauses() ; i++) {
        cl = _clauses[i];
        if (IsDebug()) {
            cout << cl->GetString();
        }
        bool isSatClause = false;
        for (unsigned int j = 0 ; j < cl->GetSize() ; j++) {
            lit = cl->Get(j);
            if (lit->IsSat()) {
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

    return result;
}

bool SolverSimulate::NextAssignment() {
    for (unsigned int i = 1 ; i < GetNumOfVariables() + 1 ; i++) {
        if (_variables[i]->GetAssignedValue()) {
            _variables[i]->Assign(false);
        } else {
            _variables[i]->Assign(true);
            return true;
            break;
        }
    }
    return false;
}

void SolverSimulate::InitVariables(const unsigned int n) {
    for (unsigned i = 0 ; i < n+1 ; i++) {
        _variables.push_back(new Variable(i));
    }
}

Clause<Literal>* SolverSimulate::ParseClause(string s) {
    int lit;
    istringstream iss(s);
    Clause<Literal> *c = new Clause<Literal>();
    Literal *pLit = NULL;

    while(iss >> lit) {
        if (lit == 0) {
            break;
        } else if (lit > 0) {
            pLit = _variables[lit]->GetPosLit();
            c->Insert(pLit);
        } else {
            pLit = _variables[-lit]->GetNegLit();
            c->Insert(pLit);
        }
    }
    return c;
}

void SolverSimulate::Display() {
    for (unsigned i = 0 ; i < _clauses.size() ; i++) {
        cout << _clauses[i]->GetString() << endl;
    }
}

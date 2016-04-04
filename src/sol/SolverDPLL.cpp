#include "SolverDPLL.h"

void SolverDPLL::ReadCnf(const string cnfName) {
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

    MSG() << cnfName << " is parsed. "
          << " nVar: " << GetNumOfVariables()
          << " nClause: " << GetNumOfClauses() << endl;
    if (IsDebug()) {
        Display();
    }
}

Clause2Watch* SolverDPLL::ParseClause(string s) {
    int lit;
    istringstream iss(s);
    Clause2Watch *c = new Clause2Watch;
    Literal *pLit = NULL;

    while(iss >> lit) {
        if (lit == 0) {
            break;
        } else if (lit > 0) {
            pLit = _variables[lit]->GetPosLit();
            c->Insert(pLit);
            pLit->AddClause(c);
        } else {
            pLit = _variables[-lit]->GetNegLit();
            c->Insert(pLit);
            pLit->AddClause(c);
        }
    }
    return c;
}

string SolverDPLL::GetAssignment() { stringstream ss;
    for (unsigned int i = 1 ; i < GetNumOfVariables() + 1 ; i++) {
        ss << (_variables[i]->GetAssignedValue()? "":"-") 
           << i << ' ';
    }
    return ss.str();
}

void SolverDPLL::Solve()
{
    _result = Preprocess();

    if (_result != UNDEF) {
        return;
    }
    while(1) {
        _result = Deduce(Decide());
        if (_result == UNDEF) {
            Level backToLevel = Analyze();
            if (backToLevel < 0) {
                _result = UNSAT;
                return;
            } else {
                BackTrack(backToLevel);
            }
        } else if (_result == SAT) {
            return;
        }
    }
}

void SolverDPLL::InitVariables(const unsigned int n) {
    for (unsigned i = 0 ; i < n+1 ; i++) {
        _variables.push_back(new Variable(i));
        _variables.back()->InitLiterals<Literal>();
    }
}

void SolverDPLL::Display() {
    for (unsigned i = 0 ; i < _clauses.size() ; i++) {
        cout << _clauses[i]->GetString() << endl;
    }
}

Solver::Result SolverDPLL::Preprocess()
{
    return Solver::UNDEF;
}

Literal* SolverDPLL::Decide()
{
    for (unsigned int i = 0 ; i < _variables.size() ; i++) {
        if (_variables[i]->IsAssigned()) {
            continue;
        }

        if (_variables[i]->GetPosLit()->HasNoRelatedClauses()) {
            _variables[i]->Assign(false);
            return _variables[i]->GetNegLit();
        }

        if (_variables[i]->GetNegLit()->HasNoRelatedClauses()) {
            _variables[i]->Assign(true);
            return _variables[i]->GetPosLit();
        }

        _variables[i]->Assign(false);
        return _variables[i]->GetNegLit();
    }

    return NULL;
}

Solver::Result SolverDPLL::Deduce(Literal* lit)
{
    assert(lit);

    queue<Literal*> assign;
    //Literal* currAssign = lit;

    do {
        ;
    } while (! assign.empty());

    return Solver::UNDEF;
}

Level SolverDPLL::Analyze()
{
    return Solver::UNDEF;
}

void SolverDPLL::BackTrack(Level lv)
{
    ;
}

// ImplicationGraph
bool ImplicationGraph::BCP() {
    Literal* lit = _decides.back();
    Variable* var = lit->GetVariable();
    Literal* compLit = (lit->IsPos()? var->GetNegLit() : var->GetPosLit());
    Clause2Watch* cl;
    list<Clause*>::iterator cit;
    queue<Literal*> impLits;

    impLits.push(compLit);

    while (! impLits.empty()) {
        lit = impLits.front();
        impLits.pop();
        for (cit = lit->_clauses.begin() ; cit != lit->_clauses.end() ; cit++) {
            cl = dynamic_cast<Clause2Watch*>(*cit);
            cl->Update2Watch(lit);

            if (cl->GetWatch1()->IsSat() || cl->GetWatch2()->IsSat()) {
                continue;
            } else if (cl->GetWatch1()->IsUnsat() && cl->GetWatch2()->IsUnsat()) {
                return false;
            }  else if (cl->GetWatch1()->IsUnsat()) {
                compLit = cl->GetWatch2()->GetComplementLiteral();
                impLits.push(compLit);
                lit->PushChildImpEdge(cl);
                cl->PushChildImpNode(compLit);
            } else if (cl->GetWatch2()->IsUnsat()) {
                compLit = cl->GetWatch1()->GetComplementLiteral();
                impLits.push(compLit);
                lit->PushChildImpEdge(cl);
                cl->PushChildImpNode(compLit);
            } else {
                continue;
            }
        }
    }

    return true;
}

Level ImplicationGraph::ConflictAnalyze() {
    //Literal* lit = _decides.back();
    return 0;
}






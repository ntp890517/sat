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

void SolverDPLL::Solve() {
    return;
}

string SolverDPLL::GetAssignment() { stringstream ss;
    for (unsigned int i = 1 ; i < GetNumOfVariables() + 1 ; i++) {
        ss << (_variables[i]->GetAssignedValue()? "":"-") 
           << i << ' ';
    }
    return ss.str();
}

void SolverDPLL::Display() {
    for (unsigned i = 0 ; i < _clauses.size() ; i++) {
        cout << _clauses[i]->GetString() << endl;
    }
}

void SolverDPLL::InitVariables(const unsigned int n) {
    for (unsigned i = 0 ; i < n+1 ; i++) {
        _variables.push_back(new Variable(i));
        _variables.back()->InitLiterals<LiteralDPLL>();
    }
}

ClauseDPLL* SolverDPLL::ParseClause(string s) {
    int lit;
    istringstream iss(s);
    ClauseDPLL *c = new ClauseDPLL;
    LiteralDPLL *pLit = NULL;

    while(iss >> lit) {
        if (lit == 0) {
            break;
        } else if (lit > 0) {
            pLit = static_cast<LiteralDPLL*>(_variables[lit]->GetPosLit());
            c->Insert(pLit);
        } else {
            pLit = static_cast<LiteralDPLL*>(_variables[-lit]->GetNegLit());
            c->Insert(pLit);
        }
    }

    c->GetWatch1()->AddClause(c);
    c->GetWatch2()->AddClause(c);
    return c;
}

LiteralDPLL* SolverDPLL::Decide() {
    Variable* v;
    
    for (unsigned int i = 1 ; i < _variables.size() ; i++) {
        v = _variables[i];
        if (! v->IsAssigned()) {
            return static_cast<LiteralDPLL*>(v->GetPosLit());
        }
    }

    return NULL;
}

bool SolverDPLL::BCP(LiteralDPLL* assign) {
    _impGraph.AddDecideNode(assign);

    queue<LiteralDPLL*> impLits;
    LiteralDPLL* lit;
    LiteralDPLL* compLit;
    LiteralDPLL* impLit;
    list<Clause*>::iterator cit;
    ClauseDPLL* cls;

    impLits.push(assign);

    while (! impLits.empty()) {
        lit = impLits.front();
        impLits.pop();
        compLit = lit->GetComplementLiteral();

        for (cit = compLit->GetClausesBegin() ; cit != compLit->GetClausesEnd() ; cit++) {
            cls = static_cast<ClauseDPLL*>(*cit);
            impLit = cls->Deduce(lit);
            if (impLit->IsUnsat()) {
                _impGraph.Conflict(impLit, impLit->GetComplementLiteral());
                return false;
            } else if (impLit) {
                impLits.push(impLit);
                lit->AddOutEdge(cls);
                cls->AddInNode(lit);
                cls->AddOutNode(impLit);
                impLit->AddInEdge(cls);
            } else {
                continue;
            }
        }
    }

    return true;
}


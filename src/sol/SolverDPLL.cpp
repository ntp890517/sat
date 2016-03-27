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
    LiteralDP *pLit = NULL;

    while(iss >> lit) {
        if (lit == 0) {
            break;
        } else if (lit > 0) {
            pLit = static_cast<LiteralDP*>(_variables[lit]->GetPosLit());
            c->Insert(pLit);
            pLit->AddClause(c);
        } else {
            pLit = static_cast<LiteralDP*>(_variables[-lit]->GetNegLit());
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
        _variables.push_back(new VariableDP(i));
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

LiteralDP* SolverDPLL::Decide()
{
    for (unsigned int i = 0 ; i < _variables.size() ; i++) {
        if (_variables[i]->IsAssigned()) {
            continue;
        }

        if (static_cast<LiteralDP*>(_variables[i]->GetPosLit())->HasNoRelatedClauses()) {
            _variables[i]->Assign(false);
            return static_cast<LiteralDP*>(_variables[i]->GetNegLit());
        }

        if (static_cast<LiteralDP*>(_variables[i]->GetNegLit())->HasNoRelatedClauses()) {
            _variables[i]->Assign(true);
            return static_cast<LiteralDP*>(_variables[i]->GetPosLit());
        }

        _variables[i]->Assign(false);
        return static_cast<LiteralDP*>(_variables[i]->GetNegLit());
    }

    return NULL;
}

Solver::Result SolverDPLL::Deduce(LiteralDP* lit)
{
    assert(lit);
    _impGraph.push_back(vector<pair<LiteralDP*, Clause2Watch*> > ());
    _impGraph.back().push_back(make_pair(lit, (Clause2Watch*)NULL));

    queue<LiteralDP*> assign;
    //LiteralDP* currAssign = lit;

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


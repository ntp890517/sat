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

Clause* SolverDPLL::ParseClause(string s) {
    int lit;
    istringstream iss(s);
    Clause *c = new Clause();
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
        Decide();
        while(true) {
            _result = Deduce();
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
            } else {
                break;
            }
        }
    }
}

void SolverDPLL::InitVariables(const unsigned int n) {
    for (unsigned i = 0 ; i < n+1 ; i++) {
        _variables.push_back(new Variable(i));
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

void SolverDPLL::Decide()
{
    ;
}

Solver::Result SolverDPLL::Deduce()
{
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


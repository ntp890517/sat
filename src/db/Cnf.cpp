#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Cnf.h"

Cnf::Cnf(const string cnfName) {
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
            InitVariable(nVar);
        } else if (ss.peek() == '0') {
            break;
        } else {
            _clauses.push_back(ParseClause(ss.str()));
        }
    }

    cout << cnfName << " is parsed. "
         << " nVar: " << GetNumOfVariable()
         << " nClause: " << GetNumOfClause() << endl;
    fin.close();
}

void Cnf::Display() {
    for (unsigned i = 0 ; i < _clauses.size() ; i++) {
        cout << _clauses[i]->GetString() << endl;
    }
}

void Cnf::InitVariable(const unsigned int n) {
    for (unsigned i = 0 ; i < n+1 ; i++) {
        _variable.push_back(new Variable(i));
    }
}

Clause<Literal>* Cnf::ParseClause(string s) {
    int lit;
    istringstream iss(s);
    Clause<Literal> *c = new Clause<Literal>();
    Literal *pLit = NULL;

    while(iss >> lit) {
        if (lit == 0) {
            break;
        } else if (lit > 0) {
            pLit = _variable[lit]->GetPosLit();
            c->Insert(pLit);
        } else {
            pLit = _variable[-lit]->GetNegLit();
            c->Insert(pLit);
        }
    }
    return c;
}

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
            _clauses.push_back(new Clause<Literal>(ss.str()));
        }
    }

    cout << cnfName << " is parsed. "
         << " nVar: " << GetNumOfVariable()
         << " nClause: " << nCl << endl;
    fin.close();
}

void Cnf::InitVariable(const unsigned int n) {
    for (unsigned i = 0 ; i < n+1 ; i++) {
        _variable.push_back(new Variable(i));
    }
}

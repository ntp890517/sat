#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Cnf.h"

Cnf::Cnf(const string cnfName) {
    ifstream fin;
    fin.open(cnfName.c_str());

    string line;
    string buf;
    while(getline(fin, line)) {
        istringstream ss(line);
        if (ss.peek() == 'c') {
            continue;
        } else if (ss.peek() == 'p') {
            ss >> buf >> buf >> _nVariable >> _nClause;
        } else if (ss.peek() == '0') {
            break;
        } else {
            _clauses.push_back(new Clause<Literal>(ss.str()));
        }
    }

    cout << cnfName << " is parsed. "
         << " nVar: " << _nVariable
         << " nClause: " << _nClause << endl;
    fin.close();
}

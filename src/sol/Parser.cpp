#include "Parser.h"
#include <fstream>
#include <cctype>

Cnf* Parser::ReadCnf(const string fName, CnfBuilder* b) {
    ifstream fin;
    fin.open(fName.c_str());
    unsigned int nVar, nCl;

    string line;
    string buf;
    b->Init();
    try {
        while(getline(fin, line)) {
            istringstream ss(line);
            int c = ss.peek();
            if (c == 'c') {
                continue;
            } else if (c == 'p') {
                ss >> buf >> buf >> nVar >> nCl;
                b->BuildVariableTable(nVar);
            } else {
                int lit;
                ss >> lit;
                if (ss.good()) {
                    b->BuildClause(line);
                } else {
                    throw string("Parsing Failed. Fail line:\"") +
                          line + string("\"");
                }
            }
        }
    } catch (string s) {
        ERROR() << s << endl;
        exit(1);
    }

    fin.close();
    b->PostProcess();

    MSG() << fName << " is parsed. "
          << " nVar: " << b->GetCnf()->GetVariablesSize()
          << " nClause: " << b->GetCnf()->GetClausesSize() << endl;

    return b->GetCnf();
}

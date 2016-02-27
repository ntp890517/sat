#ifndef CLAUSE_H_
#define CLAUSE_H_

#include <vector>
#include <sstream>
#include <bitset>

#include "Literal.h"

using namespace std;

class Clause {
    public:
        Clause(const string s);

        unsigned int GetSize() {return _literals.size();}

        Literal* GetLiteral(unsigned int idx) {return _literals[idx];}
        string GetString();
    private:
        vector<Literal*> _literals;
};

#endif

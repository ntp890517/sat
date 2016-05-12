#include "Cnf.h"

using namespace std;

void Cnf::Dump() {
    for (unsigned i = 0 ; i < _clauses.size() ; i++) {
        cout << _clauses[i]->GetString() << endl;
    }
}

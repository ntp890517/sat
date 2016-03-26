#include "../db/Clause.h"
#include <iostream>

using namespace std;

// Clause = ( 1 -2 3 )
int main() {
    Clause* c = new Clause();

    Variable* var1 = new Variable(1);
    Variable* var2 = new Variable(2);
    Variable* var3 = new Variable(3);

    c->Insert(var1->GetPosLit());
    c->Insert(var2->GetNegLit());
    c->Insert(var3->GetPosLit());

    cout << "Clause = ( 1 -2 3 )" << endl;
    
    cout << "[TEST] GetString()" << endl;
    cout << c->GetString() << endl;

    cout << "[TEST] GetSize()" << endl;
    cout << c->GetSize() << endl;

    cout << "[TEST] Get(0)" << endl;
    cout << c->Get(0)->GetNumeric() << endl;

    return 0;
}

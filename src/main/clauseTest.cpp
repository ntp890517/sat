#include "../db/Clause.h"
#include "../db/Clause2Watch.h"
#include <iostream>

using namespace std;

// Clause = ( 1 -2 3 )
int main() {
    Clause* c = new Clause();

    Variable* var1 = new Variable(1);
    Variable* var2 = new Variable(2);
    Variable* var3 = new Variable(3);

    var1->InitLiterals<Literal>();
    var2->InitLiterals<Literal>();
    var3->InitLiterals<Literal>();

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

    Clause2Watch* c2w = new Clause2Watch();
    c2w->Insert(var1->GetPosLit());
    c2w->Insert(var2->GetNegLit());
    c2w->Insert(var3->GetPosLit());

    cout << "Clause2Watch = (1 -2 3)" << endl;
    c2w->Setup2Watch();

    cout << "[TEST] Original (w1, w2)" << endl;
    cout << c2w->GetWatch1()->GetString() << ", " << c2w->GetWatch2()->GetString() << endl;

    cout << "[TEST] 1=F (w1, w2)" << endl;
    var1->Assign(false);
    c2w->Update2Watch(var1->GetPosLit());
    cout << c2w->GetWatch1()->GetString() << ", " << c2w->GetWatch2()->GetString() << endl;

    cout << "[TEST] 2=T (w1, w2)" << endl;
    var2->Assign(true);
    Literal * impLit = c2w->Update2Watch(var2->GetNegLit());
    cout << c2w->GetWatch1()->GetString() << ", " << c2w->GetWatch2()->GetString() << endl;
    cout << "imply: " << impLit->GetString() << endl;

    return 0;
}

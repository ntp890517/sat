#include "../db/Clause.h"
#include "../db/Clause2Watch.h"
#include "../test/Test.h"
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

    Test clsTest("Clause (1 -2 3)");
    
    clsTest.TEST_BEGIN("GetString()");
    clsTest.TEST_EQUAL(string("1 -2 3"), c->GetString());
    clsTest.TEST_END();

    clsTest.TEST_BEGIN("GetSize()");
    clsTest.TEST_EQUAL(3, int(c->GetSize()));
    clsTest.TEST_END();

    clsTest.TEST_BEGIN("Get(0)");
    clsTest.TEST_EQUAL(1, c->Get(0)->GetNumeric());
    clsTest.TEST_END();

    clsTest.REPORT();

    Clause2Watch* c2w = new Clause2Watch();
    c2w->Insert(var1->GetPosLit());
    c2w->Insert(var2->GetNegLit());
    c2w->Insert(var3->GetPosLit());

    Test c2wTest("Clause2Watch (1 -2 3)");

    c2w->Setup2Watch();

    c2wTest.TEST_BEGIN("watch1");
    c2wTest.TEST_EQUAL(1, c2w->GetWatch1()->GetNumeric());
    c2wTest.TEST_END();

    c2wTest.TEST_BEGIN("watch2");
    c2wTest.TEST_EQUAL(-2, c2w->GetWatch2()->GetNumeric());
    c2wTest.TEST_END();

    c2wTest.TEST_BEGIN("watch1 update");
    var1->Assign(false);
    c2w->Update2Watch(var1->GetPosLit());
    c2wTest.TEST_EQUAL(3, c2w->GetWatch1()->GetNumeric());
    c2wTest.TEST_END();

    c2wTest.TEST_BEGIN("imply");
    var2->Assign(true);
    Literal * impLit = c2w->Update2Watch(var2->GetNegLit());
    c2wTest.TEST_EQUAL(3, impLit->GetNumeric());
    c2wTest.TEST_END();

    c2wTest.REPORT();

    return 0;
}

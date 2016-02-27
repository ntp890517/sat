#include "Literal.h"

using namespace std;

Literal::Literal(const int v) {
    if (v > 0) {
        _v = (v << 1);
    } else if (v < 0) {
        _v = (-v << 1) + 1;
    } else {
        cout << "WARNING: illegal literal " << v << endl;
    }
}

string Literal::GetString() {
    stringstream ss;
    ss << (this->IsPos()? "":"-") << this->GetVariable();
    return ss.str();
}

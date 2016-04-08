#include "Test.h"

void Test::TEST_EQUAL(unsigned e, unsigned r) {
    _currComponent->_valid = (e != r)? false : true;

    if (! _currComponent->_valid) {
        _currComponent->_expected = to_string(e);
        _currComponent->_result = to_string(r);
    }
}

void Test::TEST_EQUAL(int e, int r) {
    _currComponent->_valid = (e != r)? false : true;

    if (! _currComponent->_valid) {
        _currComponent->_expected = to_string(e);
        _currComponent->_result = to_string(r);
    }
}

void Test::TEST_EQUAL(string e, string r) {
    _currComponent->_valid = (e != r)? false : true;

    if (! _currComponent->_valid) {
        _currComponent->_expected = e;
        _currComponent->_result = r;
    }
}

void Test::REPORT() {
    cout << "TEST: " << _name << endl;
    cout << setiosflags( ios::left )
         << setw(5) << "Idx"
         << setw(15) << "Target"
         << setw(7) << "Status"
         << setw(15) << "Expect"
         << setw(15) << "Result" << endl;
    cout << "=====================================================" << endl;
    for (unsigned int i = 0 ; i < _testComponents.size() ; i++) {
        cout << setiosflags( ios::left )
             << setw(5) << i+1
             << setw(15) << _testComponents[i]->_name
             << setw(7) << (_testComponents[i]->_valid ? "PASS":"FAIL");

        if (! _testComponents[i]->_valid) {
            cout << setw(15) << _testComponents[i]->_expected
                 << setw(15) << _testComponents[i]->_result << endl;
        } else {
            cout << endl;
        }
    }

    cout << endl;
}

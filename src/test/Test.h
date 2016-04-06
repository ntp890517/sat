#ifndef _TEST_H_
#define _TEST_H_

#include <string>
#include <vector>
#include <typeinfo>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

class Test;

class TestComponent {
    friend Test;

    public:
        TestComponent(string name) : _name(name), _valid(false) {};
    private:
        string _name;
        bool _valid;

        string _expected;
        string _result;
};

class Test {
    public:
        Test(string name) : _name(name) {};

        void TEST_BEGIN(string s) {_currComponent = new TestComponent(s);}
        void TEST_END() {_testComponents.push_back(_currComponent);}

        void TEST_EQUAL(unsigned e, unsigned r);
        void TEST_EQUAL(int e, int r);
        void TEST_EQUAL(string e, string r);
        void REPORT();
    private:
        string _name;
        TestComponent* _currComponent;
        vector<TestComponent*> _testComponents;
};

#endif

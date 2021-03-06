#ifndef CNF_BUILDER_H_ 
#define CNF_BUILDER_H_ 

#include "../db/Cnf.h"

class CnfBuilder {
    public:
        CnfBuilder() : _isDone(false), _cnf(nullptr) {};
        virtual void Init() = 0;
        virtual void BuildVariableTable(unsigned nrVars) = 0;
        virtual void BuildClause(string s) = 0;
        virtual void PostProcess() {};

        Cnf* GetCnf();
    protected:
        bool _isDone;
        Cnf* _cnf;
};

class DpllCnfBuilder : public CnfBuilder {
    public:
        virtual void Init() {_cnf = new Cnf;}
        virtual void BuildVariableTable(unsigned nrVars);
        virtual void BuildClause(string s);
        virtual void PostProcess();
    private:
        void Setup2WatchLiteral();
};

#endif

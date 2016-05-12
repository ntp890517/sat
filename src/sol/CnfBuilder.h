#ifndef CNF_BUILDER_H_ 
#define CNF_BUILDER_H_ 

class CnfBuilder {
    public:
        virtual void BuildVariableTable(unsigned nrVars) = 0;
        virtual void BuildClause(string s) = 0;
        virtual void PostProcess() {};
};

#endif

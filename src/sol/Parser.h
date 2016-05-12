#ifndef PARSER_H_
#define PARSER_H_

#include "CnfBuilder.h"

class Parser {
    public:
        Cnf* ReadCnf(const string, CnfBuilder*);
};

#endif

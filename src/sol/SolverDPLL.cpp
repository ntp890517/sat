#include "SolverDPLL.h"

void SolverDPLL::ReadCnf(const string cnfName) {
    ifstream fin;
    fin.open(cnfName.c_str());
    unsigned int nVar, nCl;

    string line;
    string buf;
    while(getline(fin, line)) {
        istringstream ss(line);
        if (ss.peek() == 'c') {
            continue;
        } else if (ss.peek() == 'p') {
            ss >> buf >> buf >> nVar >> nCl;
            InitVariables(nVar);
        } else if (ss.peek() == '0') {
            break;
        } else {
            _clauses.push_back(ParseClause(ss.str()));
        }
    }

    fin.close();

    MSG() << cnfName << " is parsed. "
          << " nVar: " << GetNumOfVariables()
          << " nClause: " << GetNumOfClauses() << endl;
    if (IsDebug()) {
        Display();
    }
}

void SolverDPLL::Solve() {
    return;
}

string SolverDPLL::GetAssignment() { stringstream ss;
    for (unsigned int i = 1 ; i < GetNumOfVariables() + 1 ; i++) {
        ss << (_variables[i]->GetAssignedValue()? "":"-") 
           << i << ' ';
    }
    return ss.str();
}

void SolverDPLL::Display() {
    for (unsigned i = 0 ; i < _clauses.size() ; i++) {
        cout << _clauses[i]->GetString() << endl;
    }
}

void SolverDPLL::InitVariables(const unsigned int n) {
    for (unsigned i = 0 ; i < n+1 ; i++) {
        _variables.push_back(new Variable(i));
        _variables.back()->InitLiterals<LiteralDPLL>();
    }
}

ClauseDPLL* SolverDPLL::ParseClause(string s) {
    int lit;
    istringstream iss(s);
    ClauseDPLL *c = new ClauseDPLL;
    LiteralDPLL *pLit = NULL;

    while(iss >> lit) {
        if (lit == 0) {
            break;
        } else if (lit > 0) {
            pLit = static_cast<LiteralDPLL*>(_variables[lit]->GetPosLit());
            c->Insert(pLit);
        } else {
            pLit = static_cast<LiteralDPLL*>(_variables[-lit]->GetNegLit());
            c->Insert(pLit);
        }
    }

    c->GetWatch1()->AddClause(c);
    c->GetWatch2()->AddClause(c);
    return c;
}

LiteralDPLL* SolverDPLL::Decide() {
    Variable* v;
    
    for (unsigned int i = 1 ; i < _variables.size() ; i++) {
        v = _variables[i];
        if (! v->IsAssigned()) {
            return static_cast<LiteralDPLL*>(v->GetPosLit());
        }
    }

    return NULL;
}

// ImplicationGraph
//bool ImplicationGraph::BCP() {
//    Literal* lit = _decides.back();
//    Variable* var = lit->GetVariable();
//    Literal* compLit = (lit->IsPos()? var->GetNegLit() : var->GetPosLit());
//    Clause2Watch* cl;
//    list<Clause*>::iterator cit;
//    queue<Literal*> impLits;
//
//    impLits.push(compLit);
//
//    while (! impLits.empty()) {
//        lit = impLits.front();
//        impLits.pop();
//        for (cit = lit->_clauses.begin() ; cit != lit->_clauses.end() ; cit++) {
//            cl = dynamic_cast<Clause2Watch*>(*cit);
//            cl->Update2Watch(lit);
//
//            if (cl->GetWatch1()->IsSat() || cl->GetWatch2()->IsSat()) {
//                continue;
//            } else if (cl->GetWatch1()->IsUnsat() && cl->GetWatch2()->IsUnsat()) {
//                return false;
//            }  else if (cl->GetWatch1()->IsUnsat()) {
//                compLit = cl->GetWatch2()->GetComplementLiteral();
//                impLits.push(compLit);
//                lit->PushImpOutEdge(cl);
//                cl->PushImpOutNode(compLit);
//            } else if (cl->GetWatch2()->IsUnsat()) {
//                compLit = cl->GetWatch1()->GetComplementLiteral();
//                impLits.push(compLit);
//                lit->PushImpOutEdge(cl);
//                cl->PushImpOutNode(compLit);
//            } else {
//                continue;
//            }
//        }
//    }
//
//    return true;
//}
//
//Level ImplicationGraph::ConflictAnalyze() {
//    //Literal* lit = _decides.back();
//    return 0;
//}






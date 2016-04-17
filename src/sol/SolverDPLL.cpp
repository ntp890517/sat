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
        } else if (isdigit(ss.peek())) {
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
    Preprocess();

    LiteralDPLL* assign;

    while (1) {
        assign = Decide();

        if (! assign) {
            _result = SAT;
            return;
        }

        if (! BCP(assign)) {
            unsigned backToLv = Analyze();
            if (backToLv  == 0) {
                _result = UNSAT;
                return;
            } else {
                BackTrack(backToLv);
            }
        }
    }
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
    LiteralDPLL *pLit = nullptr;

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

    c->Setup2Watch();
    c->GetWatch1()->AddClause(c);
    c->GetWatch2()->AddClause(c);
    return c;
}

void SolverDPLL::Preprocess() {
    for (unsigned i = 0 ; i < _clauses.size() ; i++) {
        if (_clauses[i]->GetSize() == 1) {
            LiteralDPLL* lit = static_cast<LiteralDPLL*>(_clauses[i]->GetWatch1());
            lit->GetVariable()->Assign(lit->GetSign());
            lit->SetLevel(0);
        }
    }
    _impGraph.AddDecideNode(nullptr);
}

LiteralDPLL* SolverDPLL::Decide() {
    Variable* v;
    
    for (unsigned int i = 1 ; i < _variables.size() ; i++) {
        v = _variables[i];
        if (! v->IsAssigned()) {
            return static_cast<LiteralDPLL*>(v->GetPosLit());
        }
    }

    return nullptr;
}

bool SolverDPLL::BCP(LiteralDPLL* assign) {
    _impGraph.AddDecideNode(assign);

    queue<LiteralDPLL*> impLits;
    LiteralDPLL* lit;
    LiteralDPLL* compLit;
    LiteralDPLL* impLit;
    list<Clause*>::iterator cit;
    ClauseDPLL* cls;

    impLits.push(assign);

    while (! impLits.empty()) {
        lit = impLits.front();
        impLits.pop();

        lit->GetVariable()->Assign(lit->GetSign());
        lit->SetLevel(_impGraph.GetCurrentLevel());
        compLit = lit->GetComplementLiteral();

        for (cit = compLit->GetClausesBegin() ; cit != compLit->GetClausesEnd() ; cit++) {
            cls = static_cast<ClauseDPLL*>(*cit);
            impLit = cls->Deduce(lit);
            if (! impLit) {
                continue;
            } else if (impLit->IsUnsat()) {
                _impGraph.Conflict(impLit, impLit->GetComplementLiteral());
                return false;
            } else if (impLit) {
                impLits.push(impLit);
                lit->AddOutEdge(cls);
                cls->AddInNode(lit);
                cls->AddOutNode(impLit);
                impLit->AddInEdge(cls);
            } else {
                continue;
            }
        }
    }

    return true;
}

list<ClauseDPLL*> SolverDPLL::GetFirstUipCut() {
    list<ImplicationGraphEdge*>::iterator eit;
    list<ImplicationGraphNode*>::iterator nit;
    queue<LiteralDPLL*> nodes;
    list<ClauseDPLL*> cut;
    ClauseDPLL* ept;
    LiteralDPLL* npt;

    LiteralDPLL* uip = static_cast<LiteralDPLL*>(_impGraph.GetFirstUip());
    _uip = uip;

    nodes.push(uip);

    while (! nodes.empty()) {
        npt = nodes.front();
        nodes.pop();

        for (eit = npt->GetOutEdgesBegin() ; eit != npt->GetOutEdgesEnd() ; eit++) { 
            ept = static_cast<ClauseDPLL*>(*eit);
            for (nit = ept->GetOutNodesBegin() ; nit != ept->GetOutNodesEnd() ; nit++) {
                npt = static_cast<LiteralDPLL*>(*nit);
                nodes.push(npt);
            }

            LiteralDPLL* w1 = static_cast<LiteralDPLL*>(ept->GetWatch1());
            LiteralDPLL* w2 = static_cast<LiteralDPLL*>(ept->GetWatch1());
            if (w1->GetLevel() != _impGraph.GetCurrentLevel() ||
                w2->GetLevel() != _impGraph.GetCurrentLevel() ||
                npt == uip) {
                cut.push_back(ept);
            }
        }
    }

    return cut;
}

unsigned SolverDPLL::Analyze() {
    list<ClauseDPLL*> uipCut = GetFirstUipCut();
    list<ClauseDPLL*>::iterator cit;
    list<LiteralDPLL*>::iterator lit;
    ClauseDPLL* cpt;
    LiteralDPLL* lpt;
    ClauseDPLL* lnCls = new ClauseDPLL;
    unsigned lowestLevel;

    lnCls->Insert(_uip);
    lowestLevel = _uip->GetLevel();

    for (cit = uipCut.begin() ; cit != uipCut.end() ; cit++) {
        cpt = *cit;
        for (unsigned i = 0 ; i < cpt->GetSize() ; i++) {
            lpt = static_cast<LiteralDPLL*>(cpt->Get(i));
            if (lpt->GetLevel() != _impGraph.GetCurrentLevel()) {
                lnCls->Insert(lpt);
                lowestLevel = (lpt->GetLevel() < lowestLevel)? 
                               lpt->GetLevel() : lowestLevel;
            }
        }
    }

    lnCls->Setup2Watch();
    lnCls->GetWatch1()->AddClause(lnCls);
    lnCls->GetWatch2()->AddClause(lnCls);

    if (lnCls->GetSize() == 1) {
        lpt = static_cast<LiteralDPLL*>(lnCls->Get(0));
        lpt->GetVariable()->Assign(lpt->GetSign());
        lpt->SetLevel(0);
    }

    return 0;
}

void SolverDPLL::BackTrack(unsigned int backToLv) {
    LiteralDPLL* node;
    LiteralDPLL* nextNode;
    ImplicationGraphEdge* edge;
    queue<LiteralDPLL*> nodeQueue;
    list<ImplicationGraphEdge*>::iterator eit;
    list<ImplicationGraphNode*>::iterator nit;

    for (unsigned int lvl = backToLv ; lvl <= _impGraph.GetCurrentLevel() ; lvl++) {
        nodeQueue.push(static_cast<LiteralDPLL*>(_impGraph.GetDecideNode(lvl)));
        while (! nodeQueue.empty()) {
            node = nodeQueue.front();
            nodeQueue.pop();

            node->GetVariable()->Unassign();
            for (eit = node->GetOutEdgesBegin() ; eit != node->GetOutEdgesEnd() ; eit++) {
                edge = *eit;
                for (nit = edge->GetOutNodesBegin() ; nit != edge->GetOutNodesEnd() ; nit++) {
                    nextNode = static_cast<LiteralDPLL*>(*nit);
                    nodeQueue.push(nextNode);
                }
                edge->PurgeRelatedNodes();
            }
            node->PurgeRelatedEdges();
        }
    }
}



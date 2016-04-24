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
        } else if (ss.peek() == EOF) {
            continue;
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

    if (! Preprocess()) {
        _result = UNSAT;
        return;
    }

    LiteralDPLL* assign;

    while (1) {
        assign = Decide();

        if (! assign) {
            _result = SAT;
            return;
        }

        //cout << "[Assign] " << assign->GetString() << endl;

        if (! BCP(assign, _impGraph.GetCurrentLevel())) {
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

bool SolverDPLL::Preprocess() {
    _impGraph.AddDecideNode(nullptr);
    for (unsigned i = 0 ; i < _clauses.size() ; i++) {
        if (_clauses[i]->GetSize() == 1) {
            LiteralDPLL* lit = static_cast<LiteralDPLL*>(_clauses[i]->GetWatch1());
            if (! BCP(lit, 0)) {
                return false;
            }
        }
    }

    return true;
}

LiteralDPLL* SolverDPLL::Decide() {
    Variable* v;
    LiteralDPLL* assign;
    
    for (unsigned int i = 1 ; i < _variables.size() ; i++) {
        v = _variables[i];
        if (! v->IsAssigned()) {
            assign = static_cast<LiteralDPLL*>(v->GetPosLit());
            _impGraph.AddDecideNode(assign);
            return assign;
        }
    }

    return nullptr;
}

bool SolverDPLL::BCP(LiteralDPLL* assign, unsigned int level) {
    LiteralDPLL* lit;
    LiteralDPLL* compLit;
    LiteralDPLL* impLit;
    list<Clause*>::iterator cit;
    ClauseDPLL* cls;
    list<ClauseDPLL*> relatedClauses;
    list<ClauseDPLL*>::iterator clsIt;
    queue<pair<ClauseDPLL*, LiteralDPLL*> > imply;

    imply.push(make_pair(nullptr, assign));

    while (! imply.empty()) {
        lit = imply.front().second;
        ClauseDPLL* implyBy = imply.front().first;
        imply.pop();

        lit->GetVariable()->Assign(lit->GetSign());
        lit->SetLevel(level);
        if (implyBy) {
            lit->AddInEdge(implyBy);
            implyBy->AddOutNode(lit);
            //cout << "(" << implyBy->GetString() << ") " << lit->GetString() << endl;
            for (unsigned i = 0 ; i < implyBy->GetSize() ; i++) {
                LiteralDPLL* l = static_cast<LiteralDPLL*>(implyBy->Get(i));
                if (l == lit) {
                    continue;
                }
                l = l->GetComplementLiteral();
                if (l->GetLevel() == level) {
                    l->AddOutEdge(implyBy);
                    implyBy->AddInNode(l);
                    //cout << l->GetString() << " (" << implyBy->GetString() << ")" << endl;
                }
            }
        }
        compLit = lit->GetComplementLiteral();
        compLit->SetLevel(level);

        relatedClauses.clear();
        for (cit = compLit->GetClausesBegin() ; cit != compLit->GetClausesEnd() ; cit++) {
            relatedClauses.push_back(static_cast<ClauseDPLL*>(*cit));
        }

        for (clsIt = relatedClauses.begin() ; clsIt != relatedClauses.end() ; clsIt++) {
            cls = (*clsIt);
            impLit = cls->Deduce(lit);
            if (! impLit) {
                continue;
            } else if (impLit->IsUnsat()) {
                if (level == 0) {
                    return false;
                }
                impLit->AddInEdge(cls);
                cls->AddOutNode(impLit);
                //cout << "(" << cls->GetString() << ") " << impLit->GetString() << endl;
                for (unsigned i = 0 ; i < implyBy->GetSize() ; i++) {
                    LiteralDPLL* l = static_cast<LiteralDPLL*>(cls->Get(i));
                    if (l == impLit) {
                        continue;
                    }
                    l = l->GetComplementLiteral();
                    if (l->GetLevel() == level) {
                        l->AddOutEdge(cls);
                        cls->AddInNode(l);
                        //cout << l->GetString() << " (" << cls->GetString() << ")" << endl;
                    }
                }
                _impGraph.Conflict(impLit, impLit->GetComplementLiteral());
                return false;
            } else if (impLit) {
                imply.push(make_pair(cls, impLit));
                //cout << lit->GetString() <<" " << "(" << cls->GetString() << ") " << impLit->GetString() << endl;
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
    LiteralDPLL* lit;

    LiteralDPLL* uip = static_cast<LiteralDPLL*>(_impGraph.GetFirstUip());
    _uip = uip;

    nodes.push(uip);

    while (! nodes.empty()) {
        npt = nodes.front();
        nodes.pop();

        for (eit = npt->GetOutEdgesBegin() ; eit != npt->GetOutEdgesEnd() ; eit++) { 
            ept = static_cast<ClauseDPLL*>(*eit);
            for (nit = ept->GetOutNodesBegin() ; nit != ept->GetOutNodesEnd() ; nit++) {
                nodes.push(static_cast<LiteralDPLL*>(*nit));
            }

            for (unsigned i = 0 ; i < ept->GetSize() ; i++) {
                lit = static_cast<LiteralDPLL*>(ept->Get(i));
                if ((lit->GetLevel() != _impGraph.GetCurrentLevel() ||
                    npt == uip) &&
                    ept->IsConflictCore()) {
                    cut.push_back(ept);
                    break;
                }
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

    lnCls->Insert(_uip->GetComplementLiteral());
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

    lnCls->Unique();
    lnCls->Setup2Watch();
    lnCls->GetWatch1()->AddClause(lnCls);
    lnCls->GetWatch2()->AddClause(lnCls);
    _clauses.push_back(lnCls);
    //cout << "learnt Cls: (" << lnCls->GetString() << ")" << endl;

    if (lnCls->GetSize() == 1) {
        lpt = static_cast<LiteralDPLL*>(lnCls->Get(0));
        BackTrack(1);
        if (! BCP(lpt, 0)) {
            return 0;
        } else {
            return 1;
        }
    }

    return lowestLevel;
}

void SolverDPLL::BackTrack(unsigned int backToLv) {
    LiteralDPLL* node;
    LiteralDPLL* nextNode;
    ImplicationGraphEdge* edge;
    queue<LiteralDPLL*> nodeQueue;
    list<ImplicationGraphEdge*>::iterator eit;
    list<ImplicationGraphNode*>::iterator nit;

    for (unsigned int lvl = _impGraph.GetCurrentLevel() ; lvl >= backToLv ; lvl--) {
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
        _impGraph.PopBackDecideNode();
    }
}



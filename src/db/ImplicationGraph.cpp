#include "ImplicationGraph.h"

#include <queue>

typedef ImplicationGraphEdge ImpEdge;
typedef ImplicationGraphNode ImpNode;

bool ImplicationGraphNode::IsAllOutEdgesFlag1() {
    list<ImpEdge*>::iterator eit;

    for (eit = _outEdges.begin() ; eit != _outEdges.end() ; eit++) {
        if (! (*eit)->Flag1()) {
            return false;
        }
    }
    return true;
}

void ImplicationGraph::Conflict(ImpNode *n1, ImpNode *n2) {
    n1->AddOutEdge(&_conflictEdge);
    n2->AddOutEdge(&_conflictEdge);
    _conflictEdge.AddInNode(n1);
    _conflictEdge.AddInNode(n2);
    _conflictEdge.AddOutNode(&_conflictNode);
    _conflictNode.AddInEdge(&_conflictEdge);
}

void ImplicationGraph::ResetFlags(unsigned int lvl) {
    ImpNode* npt = GetDecideNode(lvl);
    list<ImpEdge*>::iterator eit;
    list<ImpNode*>::iterator nit;
    queue<ImpNode*> nodes;

    nodes.push(npt);

    while (! nodes.empty()) {
        npt = nodes.front();
        nodes.pop();

        npt->ResetFlags();
        for (eit = npt->GetOutEdgesBegin() ; eit != npt->GetOutEdgesEnd() ; eit++) { 
            (*eit)->ResetFlags();
            for (nit = (*eit)->GetOutNodesBegin() ; nit != (*eit)->GetOutNodesEnd() ; nit++) {
                nodes.push(*nit);
            }
        }
    }
}

ImpNode* ImplicationGraph::GetFirstUip() {
    ResetFlags(GetCurrentLevel());

    ImpNode* npt = GetConflictNode();
    queue<ImpNode*> nodes;
    list<ImpEdge*>::iterator eit;
    list<ImpNode*>::iterator nit;

    nodes.push(npt);
    npt->SetFlag1();

    do {
        npt = nodes.front();
        nodes.pop();

        if (! npt->IsAllOutEdgesFlag1()) {
            nodes.push(npt);
            continue;
        }

        npt->SetFlag2();
        npt->SetConflictCore();
        for (eit = npt->GetInEdgesBegin() ; eit != npt->GetInEdgesEnd() ; eit++) {
            for (nit = (*eit)->GetInNodesBegin() ; nit != (*eit)->GetInNodesEnd() ; nit++) {
                if ((*nit)->Flag1()) {
                    continue;
                } else {
                    nodes.push(*nit);
                    (*nit)->SetFlag1();
                }
            }
            (*eit)->SetFlag1();
            (*eit)->SetConflictCore();
        }
    } while (nodes.size() != 1);

    return nodes.front();
}

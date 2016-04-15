#include "ImplicationGraph.h"

#include <queue>

typedef ImplicationGraphEdge ImpEdge;
typedef ImplicationGraphNode ImpNode;

void ImplicationGraph::Conflict(ImpNode *n1, ImpNode *n2) {
    n1->AddOutEdge(&_conflictEdge);
    n2->AddOutEdge(&_conflictEdge);
    _conflictEdge.AddInNode(n1);
    _conflictEdge.AddInNode(n2);
    _conflictEdge.AddOutNode(&_conflictNode);
    _conflictNode.AddInEdge(&_conflictEdge);
}

ImpNode* ImplicationGraph::GetFirstUIP() {
    return nullptr;
}
#if 0
ImpNode* ImplicationGraph::GetFirstUIP() {
    ImpNode* lastNode = _decideNodes.back();
    queue<ImpNode*> nodes;
    ImpNode* npt;

    nodes.push(lastNode);

    while (! nodes.empty()) {
        npt = nodes.front();
        nodes.pop();
    }

    return npt;
}
#endif

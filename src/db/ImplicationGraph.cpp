#include "ImplicationGraph.h"

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

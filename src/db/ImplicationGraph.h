#ifndef IMPLICATION_GRAPH_H_
#define IMPLICATION_GRAPH_H_

using namespace std;

#include <list>
#include <vector>
#include <cassert>
#include <iterator>

class ImplicationGraphEdge;

class ImplicationGraphNode {
    public:
        void SetIsTraversed1() {_isTraversed1 = true;}
        void UnsetIsTraversed1() {_isTraversed1 = false;}
        bool IsTraversed1() {return _isTraversed1;}
        void SetIsTraversed2() {_isTraversed2 = true;}
        void UnsetIsTraversed2() {_isTraversed2 = false;}
        bool IsTraversed2() {return _isTraversed2;}

        void SetLevel( unsigned level) {_level = level;}
        unsigned GetLevel() {return _level;}

        void AddOutEdge(ImplicationGraphEdge* e) {_outEdges.push_back(e);}
        void AddInEdge(ImplicationGraphEdge* e) {_inEdges.push_back(e);}

        list<ImplicationGraphEdge*>::iterator GetOutEdgesBegin() {
            return _outEdges.begin();
        }
        list<ImplicationGraphEdge*>::iterator GetOutEdgesEnd() {
            return _outEdges.end();
        }

        list<ImplicationGraphEdge*>::iterator GetInEdgesBegin() {
            return _inEdges.begin();
        }
        list<ImplicationGraphEdge*>::iterator GetInEdgesEnd() {
            return _inEdges.end();
        }

        void PurgeOutEdges() {_outEdges.clear();}
        void PurgeInEdges() {_inEdges.clear();}
        void PurgeRelatedEdges() {_outEdges.clear(); _inEdges.clear();}
    private:
        bool _isTraversed1;
        bool _isTraversed2;
        unsigned _level;

        list<ImplicationGraphEdge*> _outEdges;
        list<ImplicationGraphEdge*> _inEdges;
};

class ImplicationGraphEdge {
    public:
        void SetIsTraversed1() {_isTraversed1 = true;}
        void UnsetIsTraversed1() {_isTraversed1 = false;}
        bool IsTraversed1() {return _isTraversed1;}
        void SetIsTraversed2() {_isTraversed2 = true;}
        void UnsetIsTraversed2() {_isTraversed2 = false;}
        bool IsTraversed2() {return _isTraversed2;}

        void AddOutNode(ImplicationGraphNode* n) {_outNodes.push_back(n);}
        void AddInNode(ImplicationGraphNode* n) {_inNodes.push_back(n);}

        list<ImplicationGraphNode*>::iterator GetOutNodesBegin() {
            return _outNodes.begin();
        }
        list<ImplicationGraphNode*>::iterator GetOutNodesEnd() {
            return _outNodes.end();
        }

        list<ImplicationGraphNode*>::iterator GetInNodesBegin() {
            return _inNodes.begin();
        }
        list<ImplicationGraphNode*>::iterator GetInNodesEnd() {
            return _inNodes.end();
        }

        void PurgeOutNodes() {_outNodes.clear();}
        void PurgeInNodes() {_inNodes.clear();}
        void PurgeRelatedNodes() {_outNodes.clear(); _inNodes.clear();}
    private:
        bool _isTraversed1;
        bool _isTraversed2;

        list<ImplicationGraphNode*> _outNodes;
        list<ImplicationGraphNode*> _inNodes;
};

class ImplicationGraph {
    public:
        void AddDecideNode(ImplicationGraphNode* n) {_decideNodes.push_back(n);}
        void PopBackDecideNode() {_decideNodes.pop_back();}
        ImplicationGraphNode* GetDecideNode(unsigned int level) {
            assert(level < _decideNodes.size());
            return _decideNodes[level];}

        unsigned int GetCurrentLevel() {return _decideNodes.size() - 1;}

        void Conflict(ImplicationGraphNode *n1, ImplicationGraphNode *n2);

        ImplicationGraphNode* GetConflictNode() {return &_conflictNode;}
        ImplicationGraphEdge* GetConflictEdge() {return &_conflictEdge;}
    private:
        vector<ImplicationGraphNode*> _decideNodes;
        ImplicationGraphNode _conflictNode;
        ImplicationGraphEdge _conflictEdge;
};

#endif


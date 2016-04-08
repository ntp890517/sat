#ifndef IMPLICATION_GRAPH_H_
#define IMPLICATION_GRAPH_H_

using namespace std;

#include <list>
#include <vector>

class ImplicationGraphEdge;

class ImplicationGraphNode {
    public:
        void SetIsTraversed1() {_isTraversed1 = true;}
        void UnsetIsTraversed1() {_isTraversed1 = false;}
        bool IsTraversed1() {return _isTraversed1;}
        void SetIsTraversed2() {_isTraversed2 = true;}
        void UnsetIsTraversed2() {_isTraversed2 = false;}
        bool IsTraversed2() {return _isTraversed2;}

        void AddOutEdges(ImplicationGraphEdge* e) {_outEdges.push_back(e);}
        void AddInEdges(ImplicationGraphEdge* e) {_inEdges.push_back(e);}
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

        void AddOutNodes(ImplicationGraphNode* n) {_outNodes.push_back(n);}
        void AddInNodes(ImplicationGraphNode* n) {_inNodes.push_back(n);}
    private:
        bool _isTraversed1;
        bool _isTraversed2;

        list<ImplicationGraphNode*> _outNodes;
        list<ImplicationGraphNode*> _inNodes;
};

class ImplicationGraph {
    public:
        void AddDecideNode(ImplicationGraphNode* n) {_decideNodes.push_back(n);}
    private:
        vector<ImplicationGraphNode*> _decideNodes;
};

#endif


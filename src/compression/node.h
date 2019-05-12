#ifndef NODE_H
#define NODE_H

#include <memory>

struct Node {

    typedef std::shared_ptr<Node> NodePtr;

    int weight;

    char character;

    NodePtr left;

    NodePtr right;

    bool isLeaf;

    Node(int weight, char character,
        NodePtr left, NodePtr right, bool isLeaf = false);

};

#endif // NODE_H

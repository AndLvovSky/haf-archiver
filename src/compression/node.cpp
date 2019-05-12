#include "node.h"

Node::Node(int weight, char character,
    Node::NodePtr left, Node::NodePtr right, bool isLeaf) :
    weight(weight), character(character),
    left(left), right(right), isLeaf(isLeaf) {}

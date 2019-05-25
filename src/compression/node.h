#ifndef NODE_H
#define NODE_H

#include <memory>
#include <QString>
#include "charwithsize.h"

/**
 * @brief The Node class represents node in a Haffman tree.
 */
struct Node {

    /** Node pointer. */
    typedef std::shared_ptr<Node> NodePtr;

    static NodePtr fromString(QString);

    int weight; /**< Weight of the node. */

    /** Character, that keeps node. */
    char character;

    NodePtr left; /**< Pointer to the left subtree. */

    NodePtr right; /**< Pointer to the right subtree. */

    bool isLeaf; /**< Is node a leaf. */

    /**
     * Node constructor.
     * @param weight - weight of the node.
     * @param character - character to keep.
     * @param left - pointer to the left subtree.
     * @param right - pointer to the right subtree.
     * @param isLeaf - is node a leaf.
     */
    Node(int weight, char character,
        NodePtr left, NodePtr right, bool isLeaf = false);

    QString toString();

    CharWithSize serialize();

    static Node::NodePtr deserialize(CharWithSize data);
};

#endif // NODE_H

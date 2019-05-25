#include "nodetest.h"
#include "charwithsize.h"

NodeTest::NodeTest()
{

}

void NodeTest::shouldSerializeAndDeserialze()
{
    std::vector<Node::NodePtr> nodes;
    nodes.push_back(std::make_shared<Node>(50, 'q', nullptr, nullptr, true));
    nodes.push_back(std::make_shared<Node>(0, ' ', nullptr, nullptr, false));
    nodes.push_back(std::make_shared<Node>(50000, '\0', nullptr, nullptr, true));
    nodes.push_back(std::make_shared<Node>(-34, '0', nullptr, nullptr, false));
    nodes.push_back(std::make_shared<Node>(-23424, '#', nullptr, nullptr, true));

    for (auto node: nodes) {
        CharWithSize c = node->serialize();
        Node::NodePtr copy = Node::deserialize(c);
        QVERIFY(node->weight == copy->weight);
        QVERIFY(node->character == copy->character);
        QVERIFY(node->isLeaf == copy->isLeaf);
    }
}

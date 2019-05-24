#include "nodetest.h"

NodeTest::NodeTest()
{

}

void NodeTest::shouldSerializeAndDeserializeEqually()
{
    Node::NodePtr node = std::make_shared<Node>(20, 'q', nullptr, nullptr, true);
    QByteArray s = node->serialize();
    node =  Node::deserialize(s);
    QVERIFY(node->weight == 20);
    QVERIFY(node->weight == 'q');
    QVERIFY(node->weight == true);
}

#include "node.h"
#include <QDebug>

Node::NodePtr Node::fromString(QString s)
{
    bool isLeaf = (s[0] == '+');
    char character = s[1].toLatin1();
    int weight = s.mid(2).toInt();
    return std::make_shared<Node>(weight, character, nullptr, nullptr, isLeaf);
}

Node::Node(int weight, char character,
    Node::NodePtr left, Node::NodePtr right, bool isLeaf) :
    weight(weight), character(character),
    left(left), right(right), isLeaf(isLeaf) {}

QString Node::toString()
{
    QString s;
    s.append(isLeaf ? '+' : '-');
    s.append(character);
    s.append(QString::number(weight));
    //qInfo() << "Node to string: " << s;
    return s;
}

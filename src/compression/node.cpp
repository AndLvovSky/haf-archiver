#include "node.h"
#include <QDebug>

Node::NodePtr Node::fromString(QString s)
{
    if (s.size() < 3) {
        throw std::runtime_error("Invalid node format");
    }
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

CharWithSize Node::serialize()
{
    CharWithSize c;
    c.size = 2 + sizeof(int);
    c.c = new char[c.size];
    c.c[0] = isLeaf;
    c.c[1] = character;
    memcpy(c.c + 2, &weight, sizeof(int));
    return c;
}

Node::NodePtr Node::deserialize(CharWithSize data)
{
    bool isLeaf = bool(data.c[0]);
    char character = data.c[1];
    int weight;
    memcpy(&weight, data.c + 2, sizeof(int));
    delete[] data.c;
    return std::make_shared<Node>(weight, character, nullptr, nullptr, isLeaf);
}

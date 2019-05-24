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

QByteArray Node::serialize()
{
    char* c = new char[7];
    c[6] = '\0';
    c[0] = *(char*)&isLeaf;
    c[1] = character;
    sprintf(c + 2, "%d", weight);
    QByteArray data;
    data.append(c);
    qInfo() << data.size();
    qInfo() << Node::deserialize(data)->weight;
    return data;
}

Node::NodePtr Node::deserialize(QByteArray data)
{
    bool isLeaf = bool(data[0]);
    char character = data[1];
    int weight = int(*data.mid(2).data());
    return std::make_shared<Node>(weight, character, nullptr, nullptr, isLeaf);
}

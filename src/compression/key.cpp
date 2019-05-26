#include "key.h"
#include <QDebug>

int Key::nodesCounter = 0;
QStringList Key::nodesParts = QStringList();
std::vector<char*> Key::nodes;

Key Key::fromString(QString s)
{
    QString oldBytesCountS;
    int i = 0;
    while(i < s.size() && s[i] != '/') {
        oldBytesCountS.append(s[i]);
        i++;
    } i++;
    if (i == s.size() + 1) {
        throw std::runtime_error("Invalid key format");
    }
    //qInfo() << oldBytesCountS;

    QString bitsCountS;
    while(i < s.size() && s[i] != '/') {
        bitsCountS.append(s[i]);
        i++;
    } i++;
    if (i == s.size() + 1) {
        throw std::runtime_error("Invalid key format");
    }
   // qInfo() << bitsCountS;

    s = s.mid(i);
    //qInfo() << "fromString()" << s.size() << s;
    nodesParts = s.split("@");
    nodesCounter = 0;

    // delimiters fix
    for (int i = 1; i < nodesParts.size(); i++) {
        if (nodesParts[i][0] != '+' && nodesParts[i][0] != '-' && nodesParts[i][0] != '#') {
            nodesParts[i-1].append('@').append(nodesParts[i]);
            nodesParts.removeAt(i);
        }
    }

    qInfo() << nodesParts.size() << nodesParts;
    Node::NodePtr root = deserialize();
    nodesParts.clear();
    nodesCounter = 0;
    return Key(root, oldBytesCountS.toInt(), bitsCountS.toInt());
}

Key::Key(Node::NodePtr root,
         Data::SizeType oldByteCount, Data::SizeType bitCount) :
    root(root), oldByteCount(oldByteCount), bitCount(bitCount) {}

QString Key::toString()
{
    QString s;
    s.append(QString::number(oldByteCount)).append('/');
    s.append(QString::number(bitCount)).append('/');
    s.append(stringOf(root));
    return s;
}


QString Key::stringOf(Node::NodePtr node)
{
    if (!node) {
        return "#";
    }
    // # - nullptr code
    // @ - nodes delimiter
    QString s;
    s.append(node->toString()).append('@');
    s.append(stringOf(node->left)).append('@');
    s.append(stringOf(node->right)).append('@');
    return s.mid(0, s.length() - 1);
}

Node::NodePtr Key::deserialize()
{
    if (nodesCounter >= nodesParts.length() || nodesParts[nodesCounter] == "#") {
        nodesCounter++;
        //qInfo() << "nullptr";
        return nullptr;
    }

    Node::NodePtr node = Node::fromString(nodesParts[nodesCounter]);
    //qInfo() << node->toString();
    nodesCounter++;
    //qInfo() << "Going to left";
    node->left = deserialize();
    //qInfo() << "Going to right";
    node->right = deserialize();

    return node;
}

CharWithSize Key::serialize()
{
    CharWithSize c;
    c.size = sizeof(int) * 2;
    c.c = new char[c.size];
    memcpy(c.c, &oldByteCount, sizeof(int));
    memcpy(c.c + sizeof (int), &bitCount, sizeof(int));
    c.push_back(serialize(root));
    return c;
}

CharWithSize Key::serialize(Node::NodePtr node)
{
    CharWithSize c;
    c.size = 2 + sizeof(int);
    c.c = new char[c.size];
    if (!node) {
        // nullptr node
        for (int i = 0; i < c.size; i++) {
            c.c[i] = '0';
        }
        return c;
    }

    delete[] c.c;
    c.c = node->serialize().c;
    c.push_back(serialize(node->left));
    c.push_back(serialize(node->right));
    return c;
}

Key Key::deserialize(CharWithSize c)
{
    if (c.c == nullptr) {
        throw std::runtime_error("CharWithSize c is null in Key::deserialize");
    }
    // get 2 numbers
    int oldByteCount;
    memcpy(&oldByteCount, c.c, sizeof(int));
    int bitCount;
    memcpy(&bitCount, c.c + sizeof(int), sizeof(int));

    int offset = sizeof(int) * 2;
    int nodeSize = 2 + sizeof (int);
    int nodesCount = (c.size - offset) / nodeSize;
    //split to nodes
    nodes.clear();
    for (int k = 0; k < nodesCount; k++) {
        char* node = new char[nodeSize];
        for (int i = 0; i < nodeSize; i++) {
            if (offset + k * nodeSize + i >= c.size) {
                throw std::runtime_error("CharWithSize index out of range");
            }
            node[i] = c.c[offset + k * nodeSize + i];
        }
        nodes.push_back(node);
    }

    nodesCounter = 0;
    Node::NodePtr root = deserialize2();
    return Key(root, oldByteCount, bitCount);
}


Node::NodePtr Key::deserialize2()
{
   if (nodesCounter >= nodes.size() || nodes[nodesCounter][0] == '0') {
        nodesCounter++;
        return nullptr;
    }

    CharWithSize c;
    c.size = 2 + sizeof(int);
    c.c = nodes[nodesCounter];
    Node::NodePtr node = Node::deserialize(c);
    nodesCounter++;

    node->left = deserialize2();
    node->right = deserialize2();
    return node;
//    return nullptr; - never executed?
}


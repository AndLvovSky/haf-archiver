#include "key.h"
#include <QDebug>

int Key::nodesCounter = 0;
QStringList Key::nodesParts = QStringList();

Key Key::fromString(QString s)
{
    //qInfo() << "fromString() full" << s;
    QString oldBytesCountS;
    int i = 0;
    while(s[i] != '/') {
        oldBytesCountS.append(s[i]);
        i++;
    } i++;
    //qInfo() << oldBytesCountS;

    QString bitsCountS;
    while(s[i] != '/') {
        bitsCountS.append(s[i]);
        i++;
    } i++;
   // qInfo() << bitsCountS;

    s = s.mid(i);
    //qInfo() << "fromString()" << s.size() << s;
    nodesParts = s.split("@");

    // delimiters fix
    for (int i = 1; i < nodesParts.size(); i++) {
        if (nodesParts[i][0] != '+' && nodesParts[i][0] != '-' && nodesParts[i][0] != '#') {
            nodesParts[i-1].append('@').append(nodesParts[i]);
            nodesParts.removeAt(i);
        }
    }

    //qInfo() << nodesParts.size() << nodesParts;
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
    if (nodesCounter == nodesParts.length() || nodesParts[nodesCounter] == "#") {
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

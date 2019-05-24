#ifndef NODETEST_H
#define NODETEST_H

#include <QtTest>
#include "compression/node.h"

class NodeTest: public QObject {

    Q_OBJECT

public:
    NodeTest();

private slots:
    void shouldSerializeAndDeserializeEqually();
};

#endif // NODETEST_H

#include <QtTest/QtTest>
#include "test_compression.h"

#include "nodetest.h"

int main(int argc, char* argv[]) {
    {
        NodeTest nodeTest;
        QTest::qExec(&nodeTest, argc, argv);
    }
    return 0;
}

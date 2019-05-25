#include <QtTest/QtTest>
#include "test_compression.h"
#include "nodetest.h"
#include "archiverunarchivertest.h"

int main(int argc, char* argv[]) {
    int status = 0;
    {
        {
            TestCompression obj;
            status |= QTest::qExec(&obj, argc, argv);
        }
        {
            NodeTest obj;
            status |= QTest::qExec(&obj, argc, argv);
        }
        {
            ArchiverUnarchiverTest obj;
            status |= QTest::qExec(&obj, argc, argv);
        }
    }
    return status;
}

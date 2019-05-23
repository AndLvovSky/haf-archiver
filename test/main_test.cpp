#include <QtTest/QtTest>
#include "test_compression.h"

int main(int argc, char* argv[]) {
    int status = 0;
    {
        TestCompression obj;
        status |= QTest::qExec(&obj, argc, argv);
    }
    return status;
}

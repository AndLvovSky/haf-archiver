#include <QtTest/QtTest>
#include "test_compression.h"

#include "byteinputstreamtest.h"
#include "byteoutputstreamtest.h"

int main(int argc, char* argv[]) {
    {
//        TestCompression obj;
        ByteInputStreamTest inStreamTest;
        ByteOutputStreamTest outStreamTest;
        QTest::qExec(&inStreamTest, argc, argv);
        QTest::qExec(&outStreamTest, argc, argv);
    }
    return 0;
}

#ifndef BYTEOUTPUTSTREAMTEST_H
#define BYTEOUTPUTSTREAMTEST_H

#include <QtTest>
#include "byteoutputstream.h"

using namespace std;

class ByteOutputStreamTest : public QObject {

    Q_OBJECT

public:
    ByteOutputStreamTest();

private:
    vector<string> testFilesPaths;

    void shouldWriteBytes(string filePath);

private slots:
    void testPutByte();
};

#endif // BYTEOUTPUTSTREAMTEST_H

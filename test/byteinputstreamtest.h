#ifndef BYTEINPUTSTREAMTEST_H
#define BYTEINPUTSTREAMTEST_H

#include <QtTest>
#include "byteinputstream.h"

using namespace std;

class ByteInputStreamTest : public QObject {

    Q_OBJECT

public:
    ByteInputStreamTest();

private:
    vector<string> testFilesPaths;
    unique_ptr<ByteInputStream> emptyFile;
    unique_ptr<ByteInputStream> commonWords;
    unique_ptr<ByteInputStream> englishText;
    unique_ptr<ByteInputStream> googlePage;
    unique_ptr<ByteInputStream> logSSH;
    unique_ptr<ByteInputStream> sentense;

    void shouldReturnByteByByte(string filePath);

private slots:
    void init();
    void shouldReturnFileSize();
    void shouldResetStream();
    void testGetByte();
};

#endif // BYTEINPUTSTREAMTEST_H

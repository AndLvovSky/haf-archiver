#include "byteinputstreamtest.h"

ByteInputStreamTest::ByteInputStreamTest()
{
    testFilesPaths.push_back(":/files/text/empty_file.txt");
    testFilesPaths.push_back(":/files/text/common_words.txt");
    testFilesPaths.push_back(":/files/text/english_text.txt");
    testFilesPaths.push_back(":/files/text/google.html");
    testFilesPaths.push_back(":/files/text/log_ssh.log");
    testFilesPaths.push_back(":/files/text/sentence.txt");
}

void ByteInputStreamTest::shouldReturnFileSize()
{
    try {
        QVERIFY(emptyFile->byteCount() == 0);
        QVERIFY(commonWords->byteCount() == 175418);
        QVERIFY(englishText->byteCount() == 662445);
        QVERIFY(googlePage->byteCount() == 211310);
        QVERIFY(logSSH->byteCount() == 225216);
        QVERIFY(sentense->byteCount() == 82);
    } catch(std::runtime_error err) {
        qInfo(err.what());
    }
}

void ByteInputStreamTest::shouldResetStream()
{
    ByteInputStream istream(":/files/text/english_text.txt");
    try{
        QByteArray array;
        char* expected;
        QFile file(QString::fromStdString(":/files/text/english_text.txt"));
        if (file.open(QIODevice::ReadOnly)) {
            array = file.readAll();
            file.close();
        } else {
            throw std::runtime_error("Can not open file in test method");
        }
        expected = array.data();
        for (int k = 0; k < 10; k++) {
            for (int i = 0; i < 1000; i++) {
                char byte = istream.getByte();
                QVERIFY(byte == expected[i]);
            }
            istream.reset();
        }
    } catch(std::runtime_error err) {
        qInfo(err.what());
    }
}

void ByteInputStreamTest::testGetByte()
{
    for (string path: testFilesPaths) {
        shouldReturnByteByByte(path);
    }
}

void ByteInputStreamTest::shouldReturnByteByByte(string filePath)
{
    ByteInputStream istream(filePath);
    try{
        QByteArray array;
        QFile file(QString::fromStdString(filePath));
        if (file.open(QIODevice::ReadOnly)) {
            array = file.readAll();
            file.close();
        } else {
            throw std::runtime_error("Can not open file in test method");
        }

        char* expected = array.data();
        for (int i = 0; i < istream.byteCount(); i++) {
            QVERIFY(istream.getByte() == expected[i]);
        }
    } catch(std::runtime_error err) {
        qInfo(err.what());
    }
}

void ByteInputStreamTest::init()
{
    emptyFile = make_unique<ByteInputStream>(":/files/text/empty_file.txt");
    commonWords = make_unique<ByteInputStream>(":/files/text/common_words.txt");
    englishText = make_unique<ByteInputStream>(":/files/text/english_text.txt");
    googlePage = make_unique<ByteInputStream>(":/files/text/google.html");
    logSSH = make_unique<ByteInputStream>(":/files/text/log_ssh.log");
    sentense = make_unique<ByteInputStream>(":/files/text/sentence.txt");
}

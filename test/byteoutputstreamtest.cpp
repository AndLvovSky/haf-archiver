#include "byteoutputstreamtest.h"

ByteOutputStreamTest::ByteOutputStreamTest()
{
    testFilesPaths.push_back(":/files/text/empty_file.txt");
    testFilesPaths.push_back(":/files/text/common_words.txt");
    testFilesPaths.push_back(":/files/text/english_text.txt");
    testFilesPaths.push_back(":/files/text/google.html");
    testFilesPaths.push_back(":/files/text/log_ssh.log");
    testFilesPaths.push_back(":/files/text/sentence.txt");
}

void ByteOutputStreamTest::testPutByte()
{
    for (string filePath: testFilesPaths) {
        shouldWriteBytes(filePath);
    }
}

void ByteOutputStreamTest::shouldWriteBytes(string filePath)
{
    try{
        QByteArray data;
        QFile file(QString::fromStdString(filePath));
        if (file.open(QIODevice::ReadOnly)) {
            data = file.readAll();
            file.close();
        } else {
            throw std::runtime_error("Can not open file in test method");
        }

        int separatorPos = filePath.find_last_of('/');
        string fileName = filePath.substr(separatorPos + 1, filePath.length() - separatorPos - 1);

        ByteOutputStream ostream(QDir::currentPath().toStdString() + "/" + fileName);
        for (int i = 0; i < data.size(); i++) {
            ostream.putByte(data[i]);
        }
        ostream.flush();
        ostream.close();

        QByteArray actual;
        QFile outFile(QString::fromStdString(QDir::currentPath().toStdString() + "/" + fileName));
        if (file.open(QIODevice::ReadOnly)) {
            actual = file.readAll();
            file.close();
        } else {
            throw std::runtime_error("Can not open file in test method");
        }

        QVERIFY(data.size() == actual.size());
        for (int i = 0; i < data.size(); i++) {
            QVERIFY(data[i] == actual[i]);
        }
    } catch(std::runtime_error err) {
        qInfo(err.what());
    }
}

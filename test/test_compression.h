#ifndef TEST_COMPRESSION_H
#define TEST_COMPRESSION_H

#include <QtTest>

#include "data.h"

class TestCompression : public QObject {

    Q_OBJECT

private:

    Data processData(const Data& data);

    std::string processData(const std::string& text, bool print = true);

    std::string readFromFile(QString testFileName, bool binMode = true);

public:

    TestCompression();

    ~TestCompression();

private slots:

    void test_small();

    void test_medium();

    void test_big();

};

#endif // TEST_COMPRESSION_H

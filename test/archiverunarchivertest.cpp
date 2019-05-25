#include "archiverunarchivertest.h"

ArchiverUnarchiverTest::ArchiverUnarchiverTest()
{

}

void ArchiverUnarchiverTest::test()
{
    Archiver archiver(fileNames, QDir::currentPath() + "/", "test");
    archiver.process();

    Unarchiver unarchiver(QDir::currentPath() + "/test.haf",
                          QDir::currentPath() + "/");
    unarchiver.process();

    for (QString fileName: fileNames) {
        QFile expected(fileName);
        expected.open(QIODevice::ReadOnly);
        QFileInfo expectedInfo(fileName);
        QFile actual(QDir::currentPath() + "/" + expectedInfo.completeBaseName() +
                     "." + expectedInfo.completeSuffix());
        actual.open(QIODevice::ReadOnly);
        QVERIFY(expected.size() == actual.size());

        char * expectedData = new char[expected.size()];
        expected.read(expectedData, expected.size());
        char * actualData = new char[actual.size()];
        actual.read(actualData, actual.size());

        for (int i = 0; i < expected.size(); i++) {
            QVERIFY(expectedData[i] == actualData[i]);
        }
    }
}

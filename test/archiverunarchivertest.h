#ifndef ARCHIVERUNARCHIVERTEST_H
#define ARCHIVERUNARCHIVERTEST_H

#include <QtTest>
#include <archiver.h>
#include <unarchiver.h>

class ArchiverUnarchiverTest: public QObject {

    Q_OBJECT

    QStringList fileNames = {
        ":/files/text/common_words.txt",
        ":/files/text/english_text.txt",
        ":/files/text/log_ssh.log",
        ":/files/text/google.html",
        ":/files/bin/console_app.exe",
        ":/files/bin/qt_lib.dll",
        ":/files/images/black-white.jpg",
        ":/files/images/nature.jpg",
        ":/files/images/sample.BMP",
        ":/files/other/laboratory.pdf",
        ":/files/other/sociology.docx"
    };

public:
    ArchiverUnarchiverTest();

private slots:
    void test();
};

#endif // ARCHIVERUNARCHIVERTEST_H

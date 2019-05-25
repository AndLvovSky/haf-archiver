#ifndef UNARCHIVER_H
#define UNARCHIVER_H

#include <QString>
#include <vector>
#include <QFile>
#include "archiveinfo.h"
#include "byteinputstream.h"
#include "byteoutputstream.h"
#include "compression/compressor.h"
#include "charwithsize.h"

using namespace std;

class Unarchiver
{
private:
    QString outputDirPath;

    ArchiveInfo info;

    // we track number of bytes we've read from archive to pass it
    // to the archive input stream so that decompressor can reset
    // archive input stream not to the file begin but to the begin
    // of the specific compressed data part
    int bytesCounter = 0;

    ByteInputStream in;

public:
    Unarchiver(QString archivePath, QString outputDirPath);

    void process();

    ArchiveInfo getInfo();

private:
    QString readStringLengthAndString();

    QByteArray readByteArrayLengthAndByteArray();

    void readInfo();

    CharWithSize getKey(ByteInputStream &in);
};

#endif // UNARCHIVER_H

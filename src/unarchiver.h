#ifndef UNARCHIVER_H
#define UNARCHIVER_H

#include <QString>
#include <vector>
#include <QFile>
#include "archiveinfo.h"
#include "byteinputstream.h"

using namespace std;

class Unarchiver
{
private:
    QString archivePath;

    QString outputDirPath;

    vector<unique_ptr<QFile>> outputFiles;

    ArchiveInfo info;

    int bytesCounter = 0;

    unique_ptr<ByteInputStream> archiveStream;

public:
    Unarchiver(QString archivePath, QString outputDirPath);

    void process();

    ArchiveInfo getInfo();
};

#endif // UNARCHIVER_H

#ifndef ARCHIVER_H
#define ARCHIVER_H

#include <QString>
#include <QStringList>
#include "byteoutputstream.h"

class Archiver
{
private:
    QStringList filesToArchiveUris;
    ByteOutputStream out;

public:
    Archiver(QStringList filesToArchiveUris, QString destDir, QString destFileName);

    /**
     * @brief process runs archivation of input files and writes them to the output archive
     */
    void process();

private:
    void writeFilesInfo();

    void writeStringSizeAndString(QString s);
};

#endif // ARCHIVER_H

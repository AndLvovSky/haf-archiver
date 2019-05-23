#ifndef ARCHIVER_H
#define ARCHIVER_H

#include <QString>
#include <QStringList>
#include "byteoutputstream.h"

class Archiver
{
private:
    QStringList filesToArchiveUris;
    QString destDir;
    QString destFileName;
    unique_ptr<ByteOutputStream> archiveStream;

    void writeToArchiveStream(QString s);

public:
    Archiver(QStringList filesToArchiveUris, QString destDir, QString destFileName);

    /**
     * @brief process runs archivation of input files and writes them to the output archive
     */
    void process();
};

#endif // ARCHIVER_H

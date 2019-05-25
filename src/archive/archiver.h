#ifndef ARCHIVER_H
#define ARCHIVER_H

#include <QString>
#include <QStringList>
#include "util/charwithsize.h"
#include "stream/std/byteoutputstream.h"
#include "compression/key.h"
#include "compression/compressor.h"

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

    void writeKey(Key key);

    void compressAndWrite(Key key, Compressor compressor);
};

#endif // ARCHIVER_H

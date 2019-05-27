#ifndef UNARCHIVER_H
#define UNARCHIVER_H

#include <QString>
#include <vector>
#include <QFile>
#include "info/archiveinfo.h"
#include "stream/std/byteinputstream.h"
#include "stream/std/byteoutputstream.h"
#include "compression/compressor.h"
#include "util/charwithsize.h"
#include <QObject>

using namespace std;

/**
 * @brief The Unarchiver class decompresses files from archive and writes
 * them to the output directory
 */
class Unarchiver : public QObject
{

Q_OBJECT

private:
    QString outputDirPath;

    /**
     * @brief info Information about archive
     */
    ArchiveInfo info;

    /**
     * @brief bytesCounter
     *  We track number of bytes we've read from archive to pass it
     *  to the archive input stream so that decompressor can reset
     *  archive input stream not to the file begin but to the begin
     *  of the specific compressed data part
     */
    int bytesCounter = 0;

    /**
     * @brief in Input file stream
     */
    ByteInputStream in;

    /**
     * @brief filePath path to the archive
     */
    QString filePath;

    long long fileSize;

public:
    /**
     * Constructor
     * @param archivePath full path to the archive
     * @param outputDirPath output directory path
     */
    Unarchiver(QString archivePath, QString outputDirPath);

    void process();

    ArchiveInfo getInfo();

private:
    QString readStringLengthAndString();

    QByteArray readByteArrayLengthAndByteArray();

    void readInfo();

    CharWithSize getKey(ByteInputStream &in);

public slots:

    void onDecompressedChange(long long bytes);

signals:
    void progress(QString prog);

    void progressInLine(QString msg, int line);

};

#endif // UNARCHIVER_H

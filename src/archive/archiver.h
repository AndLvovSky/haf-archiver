#ifndef ARCHIVER_H
#define ARCHIVER_H

#include <QString>
#include <QStringList>
#include "util/charwithsize.h"
#include "stream/std/byteinputstream.h"
#include "stream/std/byteoutputstream.h"
#include "compression/key.h"
#include "compression/compressor.h"

/**
 * @brief The Archiver class compresses the specified files and
 * writes them to the output archive.
 */
class Archiver : public QObject
{

    Q_OBJECT

private:
    QStringList filesToArchiveUris;
    /**
     * @brief out output file stream
     */
    ByteOutputStream out;
    std::vector<std::shared_ptr<Compressor>> compressors;
    std::vector<Key> savedKeys;
    std::vector<std::shared_ptr<ByteInputStream>> inputStreams;
    QString filePath;
    long long fileSize;
    std::vector<long long> savedFileSizes;

public:
    /**
     * Archiver constructor.
     * @param filesToArchiveUris paths to the files that which will be compressed
     * @param destDir destination directory
     * @param destFileName desination archive name
     */
    Archiver(QStringList filesToArchiveUris, QString destDir, QString destFileName);

    /**
     * Runs archivation of input files and writes them to the output archive.
     */
    void process();

private:
    /**
     * Write information about files to the archive.
     */
    void writeFilesInfo();

    /**
     * Write size of specified string and
     * the text of the string to the archive.
     * @param s string
     */
    void writeStringSizeAndString(QString s);

    /**
     * Writes Key to the archive.
     * @param key key
     */
    void writeKey(Key key);

    /**
     * Compress file that is specified in compressor
     * using key parameter and write it to the archive
     * @param key key
     * @param compressor compressor object with specified input and output streams
     */
    void compressAndWrite(Key key, std::shared_ptr<Compressor> compressor);

public slots:

    void onPreparedChange(long long bytes);

    void onCompressedChange(long long bytes);

signals:
    void progress(QString prog);

    void progressInLine(QString msg, int line);

};

#endif // ARCHIVER_H

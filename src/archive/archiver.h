#ifndef ARCHIVER_H
#define ARCHIVER_H

#include <QString>
#include <QStringList>
#include "util/charwithsize.h"
#include "stream/std/byteinputstream.h"
#include "stream/std/byteoutputstream.h"
#include "compression/key.h"
#include "compression/compressor.h"

class Archiver : public QObject
{
Q_OBJECT

private:
    QStringList filesToArchiveUris;
    ByteOutputStream out;
    std::vector<std::shared_ptr<Compressor>> compressors;
    std::vector<Key> savedKeys;
    std::vector<std::shared_ptr<ByteInputStream>> inputStreams;
    QString filePath;
    long long fileSize;
    std::vector<long long> savedFileSizes;

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

    void compressAndWrite(Key key, std::shared_ptr<Compressor> compressor);

public slots:

    void onPreparedChange(long long bytes);

    void onCompressedChange(long long bytes);

signals:
    void progress(QString prog);

    void progressInLine(QString msg, int line);

};

#endif // ARCHIVER_H

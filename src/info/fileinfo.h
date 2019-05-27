#ifndef FILEINFO_H
#define FILEINFO_H

#include <QString>
#include <QDateTime>

/**
 * @brief The FileInfo struct information about a single file
 */
struct FileInfo
{
public:
    FileInfo(){}

    QString name;
    QDateTime birthTime;
    int originalSize;
    int compressedSize;
};

#endif // FILEINFO_H

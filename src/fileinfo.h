#ifndef FILEINFO_H
#define FILEINFO_H

#include <QString>
#include <QDateTime>

struct FileInfo
{
public:
    FileInfo(){}

    QString name;
    QDateTime birthTime;
};

#endif // FILEINFO_H

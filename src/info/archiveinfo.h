#ifndef ARCHIVEINFO_H
#define ARCHIVEINFO_H

#include "fileinfo.h"
#include <vector>

struct ArchiveInfo
{
public:
    ArchiveInfo(){}

    std::vector<FileInfo> filesInfo;
};

#endif // ARCHIVEINFO_H

#ifndef ARCHIVEINFO_H
#define ARCHIVEINFO_H

#include "fileinfo.h"
#include <vector>

/**
 * @brief The ArchiveInfo struct information about archive
 */
struct ArchiveInfo
{
public:
    ArchiveInfo(){}

    std::vector<FileInfo> filesInfo;
};

#endif // ARCHIVEINFO_H

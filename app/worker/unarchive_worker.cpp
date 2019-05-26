#include "unarchive_worker.h"
#include "archive/unarchiver.h"

UnarchiveWorker::UnarchiveWorker(QString archivePath, QString outputDirPath) :
    archivePath(archivePath), outputDirPath(outputDirPath) {}

UnarchiveWorker::~UnarchiveWorker() {}

void UnarchiveWorker::process() {
    try {
        Unarchiver unarchiver(archivePath, outputDirPath);
        unarchiver.process();
    } catch(std::runtime_error err) {
        emit error(err.what());
        emit finished(false);
        return;
    }
    emit finished(true);
}

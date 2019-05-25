#include "unarchive_worker.h"
#include "archive/unarchiver.h"

UnarchiveWorker::UnarchiveWorker(QString archivePath, QString outputDirPath) :
    archivePath(archivePath), outputDirPath(outputDirPath) {}

UnarchiveWorker::~UnarchiveWorker() {}

void UnarchiveWorker::process() {
    Unarchiver unarchiver(archivePath, outputDirPath);
    unarchiver.process();
    emit finished();
}

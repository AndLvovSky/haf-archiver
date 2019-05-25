#ifndef UNARCHIVE_WORKER_H
#define UNARCHIVE_WORKER_H

#include <QObject>

class UnarchiveWorker : public QObject {

    Q_OBJECT

private:

    QString archivePath;

    QString outputDirPath;

public:

    UnarchiveWorker(QString archivePath, QString outputDirPath);

    ~UnarchiveWorker();

public slots:

    void process();

signals:

    void finished();

    void error(QString err);

};

#endif // UNARCHIVE_WORKER_H

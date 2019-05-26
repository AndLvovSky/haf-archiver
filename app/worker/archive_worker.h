#ifndef ARCHIVE_WORKER_H
#define ARCHIVE_WORKER_H

#include <QObject>

class ArchiveWorker : public QObject {

    Q_OBJECT

private:

    QStringList filesToArchiveUris;

    QString destDir;

    QString destFileName;

public:

    ArchiveWorker(QStringList filesToArchiveUris,
        QString destDir, QString destFileName);

    ~ArchiveWorker();

public slots:

    void process();

signals:

    void finished(bool good);

    void error(QString err);

};

#endif // ARCHIVE_WORKER_H

#ifndef ARCHIVE_WORKER_H
#define ARCHIVE_WORKER_H

#include <QObject>

class ArchiveWorker : public QObject {

    Q_OBJECT

private:

    static int nextId;

    int id;

    QStringList filesToArchiveUris;

    QString destDir;

    QString destFileName;

public:

    ArchiveWorker(QStringList filesToArchiveUris,
        QString destDir, QString destFileName);

    ~ArchiveWorker();

    int getId();

public slots:

    void process();

    void onProgress(QString prog);

    void onProgressInLine(QString msg, int line);

signals:

    void finished(bool good, int workerId);

    void error(QString err, int workerId);

    void progress(QString prog, int workerId);

    void progressInLine(QString msg, int workerId);

};

#endif // ARCHIVE_WORKER_H

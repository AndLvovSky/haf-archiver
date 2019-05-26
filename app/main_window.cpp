#include "main_window.h"
#include "ui_main_window.h"

#include <QFileDialog>
#include "archive/archiver.h"
#include "archive/unarchiver.h"
#include <QDebug>
#include "compression/node.h"
#include "compression/key.h"
#include <QDataStream>
#include "util/charwithsize.h"
#include "worker/archive_worker.h"
#include <QThread>
#include "worker/unarchive_worker.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionArchiving_triggered() {
    auto stw = ui->stackedWidget;
    stw->setCurrentIndex(Page::ARCHIVING);
}

void MainWindow::on_chooseFilesToArchiveButton_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    QStringList fileNames;
    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();
        ui->filesToArchiveText->setText(fileNames.join(";"));
        updateReadyToArchive();
    }
}

void MainWindow::on_chooseSaveDirectoryButton_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString directoryName;
    if (dialog.exec()) {
        directoryName = dialog.selectedFiles()[0];
        ui->saveDirectoryText->setText(directoryName);
        updateReadyToArchive();
    }
}

void MainWindow::on_archiveButton_clicked() {
    QStringList filesToArchiveUris = ui->filesToArchiveText->text().split(';');
    QString archiveDest = ui->saveDirectoryText->text();
    QString archiveName = ui->archiveNameLineEdit->text();

    ui->archiveButton->setEnabled(false);
    ui->statusBar->showMessage("archiving started", 1000);

    QThread* thread = new QThread;
    ArchiveWorker* worker = new ArchiveWorker(
        filesToArchiveUris, archiveDest, archiveName);
    worker->moveToThread(thread);
    connect(worker, SIGNAL(error(QString)), this, SLOT(archivingError(QString)));
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(progress(QString)), this, SLOT(archivingProgress(QString)));
    connect(worker, SIGNAL(finished(bool)), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished(bool)), this, SLOT(archivingFinished(bool)));
    connect(worker, SIGNAL(finished(bool)), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void MainWindow::archivingError(QString err) {
    ui->statusBar->showMessage(err, 3000);
}

void MainWindow::archivingFinished(bool good) {
    if (good) {
        ui->statusBar->showMessage("archiving completed", 1000);
    }
}

void MainWindow::archivingProgress(QString prog) {
    auto lw = ui->archivingLogWidget;
    lw->addItem(prog);
}

void MainWindow::updateReadyToArchive() {
    if (ui->filesToArchiveText->text() != "" &&
        ui->saveDirectoryText->text() != "" &&
        isFolderNameValid(ui->archiveNameLineEdit->text())) {
        ui->archiveButton->setEnabled(true);
    } else {
        ui->archiveButton->setEnabled(false);
    }
}

void MainWindow::updateReadyToUnarchive() {
    if (ui->archiveText->text() != "" &&
        ui->saveDirectoryText_2->text() != "") {
        ui->unarchiveButton->setEnabled(true);
    } else {
        ui->unarchiveButton->setEnabled(false);
    }
}

void MainWindow::on_chooseArchiveButton_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(this,
        tr("Open Archive"), QString(), tr("Archive Files (*.haf)"));
    if (fileName == "") return;
    ui->archiveText->setText(fileName);
    updateReadyToUnarchive();
}

void MainWindow::on_archiveNameLineEdit_textChanged(const QString& text) {
    updateReadyToArchive();
}

bool MainWindow::isFolderNameValid(const QString& folderName) {
    // TODO
    return folderName != "";
}

void MainWindow::on_chooseSaveDirectoryButton_2_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString directoryName;
    if (dialog.exec()) {
        directoryName = dialog.selectedFiles()[0];
        ui->saveDirectoryText_2->setText(directoryName);
        updateReadyToUnarchive();
    }
}

void MainWindow::on_actionUnarchiving_triggered() {
    auto stw = ui->stackedWidget;
    stw->setCurrentIndex(Page::UNARCHIVING);
}

void MainWindow::on_unarchiveButton_clicked() {
    // do unarchiving
    ui->unarchiveButton->setEnabled(false);
    QString s = ui->archiveText->text();
    QString s2 = ui->saveDirectoryText_2->text();
    ui->statusBar->showMessage("unarchiving started", 1000);

    QThread* thread = new QThread;
    UnarchiveWorker* worker = new UnarchiveWorker(s, s2);
    worker->moveToThread(thread);
    connect(worker, SIGNAL(error(QString)), this, SLOT(unarchivingError(QString)));
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished(bool)), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished(bool)), this, SLOT(unarchivingFinished(bool)));
    connect(worker, SIGNAL(finished(bool)), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void MainWindow::unarchivingError(QString err) {
    ui->statusBar->showMessage(err, 3000);
}

void MainWindow::unarchivingFinished(bool good) {
    if (good) {
        ui->statusBar->showMessage("unarchiving completed", 1000);
    }
}

void MainWindow::on_actionViewArchive_triggered() {
    auto stw = ui->stackedWidget;
    stw->setCurrentIndex(Page::ARCHIVE_VIEW);
}

void MainWindow::on_chooseArchiveButtonView_clicked() {
    auto fileName = QFileDialog::getOpenFileName(this,
        tr("Open Archive"), QString(), tr("Archive Files (*.haf)"));
    if (fileName == "") return;
    ui->archiveTextView->setText(fileName);
    updateReadyToView();
}

void MainWindow::updateReadyToView() {
    if (ui->archiveTextView->text() != "") {
        ui->viewArchiveButton->setEnabled(true);
    } else {
        ui->viewArchiveButton->setEnabled(false);
    }
}

void MainWindow::on_viewArchiveButton_clicked() {
    QString archivePath = ui->archiveTextView->text();
    std::vector<FileInfo> filesInfo;
    try {
        Unarchiver unarchiver(archivePath, "");
        filesInfo = unarchiver.getInfo().filesInfo;
    } catch(std::runtime_error err) {
        ui->statusBar->showMessage(err.what(), 3000);
    }

    auto tw = ui->filesTableWidget;
    QStringList sl;
    tw->setRowCount(filesInfo.size());
    tw->setColumnCount(4);
    sl << "Name" << "Bytes before" << "Bytes after" << "Last change date";
    tw->setHorizontalHeaderLabels(sl);
    tw->verticalHeader()->setVisible(false);
    tw->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tw->setStyleSheet(
        "QTableView {selection-background-color: rgba(0, 0, 255, 0.3);}");

    for (int i = 0; i < filesInfo.size(); i++) {
        auto cur = filesInfo[i];
        tw->setItem(i, 0, new QTableWidgetItem(cur.name));
        tw->setItem(i, 1, new QTableWidgetItem(QString::number(cur.originalSize)));
        tw->setItem(i, 2, new QTableWidgetItem(QString::number(cur.compressedSize)));
        tw->setItem(i, 3, new QTableWidgetItem(cur.birthTime.toString()));
    }
}

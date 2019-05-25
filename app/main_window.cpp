#include "main_window.h"
#include "ui_main_window.h"

#include <QFileDialog>
#include "archiver.h"
#include "unarchiver.h"
#include <QDebug>
#include "compression/node.h"
#include "compression/key.h"
#include <QDataStream>
#include "charwithsize.h"
#include "archive_worker.h"
#include <QThread>
#include "unarchive_worker.h"

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
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), this, SLOT(archivingFinished()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void MainWindow::archivingError(QString err) {
    ui->statusBar->showMessage(err, 1000);
}

void MainWindow::archivingFinished() {
    ui->statusBar->showMessage("archiving completed", 1000);
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
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), this, SLOT(unarchivingFinished()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void MainWindow::unarchivingError(QString err) {
    ui->statusBar->showMessage(err, 1000);
}

void MainWindow::unarchivingFinished() {
    ui->statusBar->showMessage("unarchiving completed", 1000);
}

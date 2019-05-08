#include "main_window.h"
#include "ui_main_window.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionArchiving_triggered() {
    auto stw = ui->stackedWidget;
    stw->setCurrentIndex(1);
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

void MainWindow::on_archiveButton_clicked()
{
    // do archiving
    ui->archiveButton->setEnabled(false);
    QMessageLogger().debug("Start archiving");
}

void MainWindow::updateReadyToArchive() {
    if (ui->filesToArchiveText->text() != "" &&
        ui->saveDirectoryText->text() != "") {
        ui->archiveButton->setEnabled(true);
    }
}

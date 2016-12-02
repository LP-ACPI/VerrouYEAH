#include "addbackupwindow.h"
#include <QFileDialog>

AddBackupWindow::AddBackupWindow(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
}

AddBackupWindow::~AddBackupWindow(){
    this->close();
}

void AddBackupWindow::on_newBackupButtonBox_accepted(){
    on_newBackupButtonBox_rejected();
}

void AddBackupWindow::on_newBackupButtonBox_rejected(){
    this->destroy();
}

void AddBackupWindow::on_srcDirChoose_clicked(){
    QString dossier = QFileDialog::getExistingDirectory(this);
    srcDirChoose->setText(dossier);
    srcDirChoose->setToolTip(dossier);
}

void AddBackupWindow::on_trgDirChoose_clicked(){
    QString dossier = QFileDialog::getExistingDirectory(this);
    trgDirChoose->setText(dossier);
    trgDirChoose->setToolTip(dossier);
}

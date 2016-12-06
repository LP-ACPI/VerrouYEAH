#include "addbackupwindow.h"
#include "backupitemwidget.h"
#include "homewindow.h"
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
    HomeWindow* parent = qobject_cast<HomeWindow*>(this->parent());

    Backup bc;
    bc.setName(backupNameInput->text());
    bc.setSource(srcDirChoose->text());
    bc.setTarget(trgDirChoose->text());
    bc.setComent(commentInput->toPlainText());

    parent->addBackup(bc);
    this->close();
}

void AddBackupWindow::on_newBackupButtonBox_rejected(){
     this->close();
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

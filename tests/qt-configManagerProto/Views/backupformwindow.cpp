#include "backupformwindow.h"
#include "backupitemwidget.h"
#include "homewindow.h"
#include <QFileDialog>

BackupFormWindow::BackupFormWindow(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    flag = "new";
}


BackupFormWindow::BackupFormWindow(Backup *bc,QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    backupNameInput->setText(bc->getName());
    srcDirChoose->setText(bc->getSource());
    trgDirChoose->setText(bc->getTarget());
    commentInput->setPlainText(bc->getComent());
    flag = "modif";
}

BackupFormWindow::~BackupFormWindow(){
    this->close();
}

void BackupFormWindow::on_newBackupButtonBox_accepted(){
    HomeWindow* parent = qobject_cast<HomeWindow*>(this->parent());

    Backup bc;
    bc.setName(backupNameInput->text());
    bc.setSource(srcDirChoose->text());
    bc.setTarget(trgDirChoose->text());
    bc.setComent(commentInput->toPlainText());

    if(flag=="modif")
        parent->modifBackup(bc);
    else {
        parent->addBackup(bc);

        parent->getConfig()->cryptDirectory(srcDirChoose->text(),trgDirChoose->text()+"/cryptTest");
    }
    this->close();
}

void BackupFormWindow::on_newBackupButtonBox_rejected(){
     this->close();
}


void BackupFormWindow::on_srcDirChoose_clicked(){
    QString dossier = QFileDialog::getExistingDirectory(this);
    srcDirChoose->setText(dossier);
    srcDirChoose->setToolTip(dossier);
}

void BackupFormWindow::on_trgDirChoose_clicked(){
    QString dossier = QFileDialog::getExistingDirectory(this);
    trgDirChoose->setText(dossier);
    trgDirChoose->setToolTip(dossier);
}

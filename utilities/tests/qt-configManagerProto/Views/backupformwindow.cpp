#include "backupformwindow.h"
#include "backupitemwidget.h"
#include "homewindow.h"
#include <QFileDialog>

BackupFormWindow::BackupFormWindow(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    backup = new Backup;
    flag = "new";

    setWindowTitle("Ajouter une sauvegarde");
    setWindowIcon(QPixmap(":/images/LetsEncrypt_Logo.png"));
}


BackupFormWindow::BackupFormWindow(Backup *bc,QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    backup = new Backup(*bc);

    setWindowTitle("Modifier la sauvegarde " + bc->getName());
    setWindowIcon(QPixmap(":/images/LetsEncrypt_Logo.png"));

    backupNameInput->setText(backup->getName());
    srcDirChoose->setText(backup->getSource());
    trgDirChoose->setText(backup->getTarget());
    commentInput->setPlainText(backup->getComent());

    flag = "modif";
}

BackupFormWindow::~BackupFormWindow(){
    delete backup;
    this->close();
}

void BackupFormWindow::on_newBackupButtonBox_accepted(){
    HomeWindow* parent = qobject_cast<HomeWindow*>(this->parent());

    Backup *oldBackup = new Backup(*backup);
    backup->setName(backupNameInput->text());
    backup->setSource(srcDirChoose->text());
    backup->setTarget(trgDirChoose->text());
    backup->setComent(commentInput->toPlainText());

    if(flag=="modif"){
        parent->modifBackup(*oldBackup,*backup);
    }
    else {
        parent->addBackup(*backup);
    }
    this->close();
}

void BackupFormWindow::on_newBackupButtonBox_rejected(){
     this->close();
}


void BackupFormWindow::on_srcDirChoose_clicked(){
    QString dossier = QFileDialog::getExistingDirectory();
    srcDirChoose->setText(dossier);
    srcDirChoose->setToolTip(dossier);
}

void BackupFormWindow::on_trgDirChoose_clicked(){
    QString dossier = QFileDialog::getExistingDirectory();
    trgDirChoose->setText(dossier);
    trgDirChoose->setToolTip(dossier);
}

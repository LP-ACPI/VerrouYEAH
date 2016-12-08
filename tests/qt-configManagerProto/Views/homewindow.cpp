#include "homewindow.h"
#include "backupitemwidget.h"
#include "ui_homewindow.h"
#include "authdialogwindow.h"
#include <QListWidgetItem>
#include <QMessageBox>
#include <QDebug>


HomeWindow::HomeWindow(QWidget *parent) :
    QMainWindow(parent),
    confMan(new ConfigManager)

{
    setupUi(this);

    if(confMan->noUser()){
        AuthDialogWindow* athWin = new AuthDialogWindow(this);
        athWin->show();
    } else {
        QMessageBox::information(this, "Bienvenue!",
                                 "Bienvenue  "+confMan->getUser()->getNom());
    }
    refresh();


    connect(backupList, SIGNAL(itemClicked(QListWidgetItem*)),
            this ,SLOT(onBackupItemClicked(QListWidgetItem*)));
    connect(confMan, SIGNAL(cryptInProgress(quint64,quint64)),
            this ,SLOT(cryptingProgress(quint64,quint64)));


}


HomeWindow::~HomeWindow() {
    delete confMan;
    this->close();
}

void HomeWindow::refresh(){
    backupList->clear();
    foreach(Backup bc, confMan->getUser()->getBackups()){
        QListWidgetItem *item = new QListWidgetItem;
        BackupItemWidget *bcW = new BackupItemWidget(&bc, this);

        item->setSizeHint(QSize(1,75));
        backupList->addItem(item);
        backupList->setItemWidget(item,bcW);
    }
}

void HomeWindow::addBackup(Backup &b){
    QListWidgetItem *item = new QListWidgetItem;
    BackupItemWidget *bcW = new BackupItemWidget(&b,this);

    item->setSizeHint(QSize(1,75));
    backupList->addItem(item);
    backupList->setItemWidget(item,bcW);

    confMan->addBackup(b);
    confMan->saveConfig();

    if(cryptingDone())
        bcW->setFocusPolicy(Qt::StrongFocus);
}

void HomeWindow::modifBackup(Backup &b){

    QListWidgetItem *item = backupList->currentItem();
     BackupItemWidget *bcW = qobject_cast<BackupItemWidget*>(backupList->itemWidget(item));

     b.setId(bcW->getBackup()->getId());
     bcW->setBackup(&b);

     confMan->majBackup(b);
     confMan->saveConfig();

     bcW->setFocusPolicy(Qt::StrongFocus);

}

void HomeWindow::removeBackup(Backup &b){
    confMan->delBackup(b);
     confMan->saveConfig();
    QListWidgetItem *item = backupList->currentItem();
    backupList->removeItemWidget(item);
    refresh();
}

ConfigManager* HomeWindow::getConfig() const{
    return confMan;
}

void HomeWindow::on_newBackupButton_clicked(){
    bcFormWin = new BackupFormWindow(this);

    connect(bcFormWin, SIGNAL(crypting(Backup*)),
            this ,SLOT(onBackupFormWindowAccepted(Backup*)));

    bcFormWin->show();
}

void HomeWindow::on_actionRAZ_triggered(){
    confMan->resetConfig();
    confMan->saveConfig();
    refresh();

    int reponse = QMessageBox::question(this, "Remise à zéro", "Souhaitez-vous vous authentifier à nouver ? (sinon, fermeture du programme)", QMessageBox ::Yes | QMessageBox::No);

        if (reponse == QMessageBox::Yes){
            AuthDialogWindow* athWin = new AuthDialogWindow(this);
            athWin->show();
        }   else if (reponse == QMessageBox::No)
            this->close();
}


void HomeWindow::onBackupItemClicked(QListWidgetItem *item)
{
    BackupItemWidget *bcW = qobject_cast<BackupItemWidget*>(backupList->itemWidget(item));
    Backup *bc = bcW->getBackup();
    bcFormWin = new BackupFormWindow(bc,this);
    bcFormWin->show();
}

void HomeWindow::onBackupFormWindowAccepted(Backup *bc){
    cryptProgress=new QProgressDialog(this);
    cryptProgress->resize(500, cryptProgress->height());
    cryptProgress->setMinimumDuration(0);
    cryptProgress->show();
    const QString target = bc->getTarget()+ QLatin1Char('/')+bc->getName()+ QLatin1String(".vy");
    if(confMan->cryptDirectory( bc->getSource(), target )){
        cryptProgress->close();
        emit cryptingDone();
    }
}

void HomeWindow::cryptingProgress(quint64 done, quint64 total){
    cryptProgress->setMaximum(total);
    cryptProgress->setWindowTitle("crypting..: "+ QString::number(done) + " / " +QString::number(total));
    cryptProgress->setMinimum(0);
    cryptProgress->setValue(done);
}





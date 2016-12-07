#include "homewindow.h"
#include "backupitemwidget.h"
#include "ui_homewindow.h"
#include "authdialogwindow.h"
#include <QListWidgetItem>
#include <QMessageBox>
#include <QDebug>


HomeWindow::HomeWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    confMan = new ConfigManager;

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
}


HomeWindow::~HomeWindow()
{
    delete confMan;
    this->close();
}

ConfigManager* HomeWindow::getConfig() const{
    return confMan;
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
}

void HomeWindow::modifBackup(Backup &b){

    QListWidgetItem *item = backupList->currentItem();
     BackupItemWidget *bcW = qobject_cast<BackupItemWidget*>(backupList->itemWidget(item));
     b.setId(bcW->getBackup()->getId());
     bcW->setBackup(&b);
     confMan->majBackup(b);
     confMan->saveConfig();
}

void HomeWindow::on_newBackupButton_clicked(){
    bcFormWin = new BackupFormWindow(this);
    connect(bcFormWin, SIGNAL(accepted()),
            this ,SLOT(onBackupFormWindowAccepted()));
    bcFormWin->show();
}


void HomeWindow::onBackupItemClicked(QListWidgetItem *item)
{
    BackupItemWidget *bcW = qobject_cast<BackupItemWidget*>(backupList->itemWidget(item));
    Backup *bc = bcW->getBackup();
    bcFormWin = new BackupFormWindow(bc,this);
    bcFormWin->show();
}

void HomeWindow::onBackupFormWindowAccepted(){

    QMessageBox::information(this, "cryptage!",
                             "cryptage!  ");
}

void HomeWindow::removeBackup(Backup &b){
    confMan->delBackup(b);
     confMan->saveConfig();
    QListWidgetItem *item = backupList->currentItem();
    backupList->removeItemWidget(item);
    refresh();
}

void HomeWindow::on_actionRAZ_triggered(){
    confMan->resetConfig();
    confMan->saveConfig();
    refresh();
}



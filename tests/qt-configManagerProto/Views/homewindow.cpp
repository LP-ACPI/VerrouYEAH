#include "homewindow.h"
#include "ui_homewindow.h"
#include <QListWidgetItem>
#include <QMessageBox>
#include <QDebug>


HomeWindow::HomeWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    confMan = new ConfigManager;
    athWin = new AuthDialogWindow(this);

    if(confMan->noUser()){
        athWin->show();
    } else {
        QMessageBox::information(this, "Bienvenue!",
                                 "Bienvenue utilisateur "+confMan->getUser()->getNom());
        listBackups();
        connect(backupList, SIGNAL(itemClicked(QListWidgetItem*)),
            this ,SLOT(onBackupItemClicked(QListWidgetItem*)));
    }
}


HomeWindow::~HomeWindow()
{
    delete confMan;
    this->close();
}

ConfigManager* HomeWindow::getConfig() const{
    return confMan;
}

void HomeWindow::listBackups(){
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

    confMan->getUser()->addBackup(b);
    confMan->saveConfig();
}

void HomeWindow::on_newBackupButton_clicked(){
    addWin = new AddBackupWindow(this);
    addWin->show();
}

void HomeWindow::on_addWin_closed(){

}

void HomeWindow::onBackupItemClicked(QListWidgetItem *item)
{


//TODO - identifier ce block

   if(QMessageBox::information(this, "",item->text()))
       return;

}

void HomeWindow::on_actionRAZ_triggered(){

    confMan->resetConfig();
    confMan->saveConfig();
    //tentative de raffraichissement - backupList->clear(); fait tout péter
    listBackups();
}

void HomeWindow::removeBackup(Backup &b){
//TODO - suppression individuelle
//    bizarrement, on peut plus utiliser confMan ici
//    un appel à lui fait tout péter

  qDebug() << confMan->getUser()->getNom();


//     confMan->saveConfig();
//    User u(*confMan->getUser());
//   u.removeBackup(b);
//   confMan->setUser(u);
//    QListWidgetItem &SRitem = backupList->item;
//    BackupItemWidget *bcW = new BackupItemWidget(&b,this);
// backupList->removeItemWidget(item);
}

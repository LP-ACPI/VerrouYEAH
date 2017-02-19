#include "mainwindow.h"
#include "authdialog.h"
#include "progressdialog.h"

#include <QtGui>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    newBackupButton->setAcceptDrops(true);
    UsersBackupController::getInstance().setCurrentUser();
    initBackupList();

    connect(backupList, SIGNAL(itemClicked(QListWidgetItem*)),
            this ,SLOT(onBackupItemClicked(QListWidgetItem*)));

}

MainWindow::~MainWindow(){
    if(detailBakcupDialog)
        delete detailBakcupDialog;
    if(backupForm)
        delete backupForm;
    if(userForm)
        delete userForm;
    close();
}

void MainWindow::initBackupList(){

    for(std::map<std::string,std::string> info
        : UsersBackupController::getInstance().getUsersBackupInfoList())
        addBackupItem(info);

}

void MainWindow::addBackupItem(std::map<std::string,std::string> backup_info){
    QListWidgetItem *item = new QListWidgetItem;
    BackupWidget *bcW = new BackupWidget(this);
    bcW->setBackupInfo(backup_info);

    item->setSizeHint(QSize(1,80));
    backupList->addItem(item);
    backupList->setItemWidget(item,bcW);
    backupWidgetList.append(bcW);

    backupList->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(bcW,SIGNAL(removed(std::string)),this,SLOT(onBackupDeleted(std::string)));
}

void MainWindow::on_newBackupButton_clicked(){
    backupForm = new BackupForm(this);
    backupForm->show();
}

void MainWindow::on_actionUtilisateur_triggered(){
    userForm = new UserForm(this);
    userForm->show();
}

void MainWindow::on_actionDeconnexion_triggered(){
    AuthDialog authDialog;
    authDialog.show();
    close();
    authDialog.exec();
}

void MainWindow::on_actionDecryptDestination_triggered(){
    if(!QDir("decrypt").exists())
        actionDecryptDestination->setDisabled(true);
    QString path = QDir::toNativeSeparators("decrypt");
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void MainWindow::onBackupItemClicked(QListWidgetItem *backupItem){
     BackupWidget *bcW = qobject_cast<BackupWidget*>(backupList->itemWidget(backupItem));
     detailBakcupDialog = new BackupDetailsDialog(bcW->getBackupKey(),this);
     detailBakcupDialog->show();
}

void MainWindow::onBackupAdd(std::map<std::string, std::string> generatedBcInfo){
    addBackupItem(generatedBcInfo);
}

void MainWindow::onBackupDeleted(std::string backupKey){

    int row = 0;
    for(BackupWidget *bcW: backupWidgetList){
        if(bcW->getBackupKey() == backupKey){
            backupList->takeItem(row);
            backupWidgetList.removeAt(row);
        }
        ++row;

}
    UsersBackupController::getInstance().deleteUsersBackup(backupKey);
}

void MainWindow::on_recoverBackupButton_clicked(){

}

void MainWindow::on_favoriteTargetsButton_clicked(){
   TargetChoiceDialog *targetChoice = new TargetChoiceDialog(this);
   targetChoice->show();
}


void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls()){
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> droppedUrls = event->mimeData()->urls();
     int droppedUrlCnt = droppedUrls.size();
     for(int i = 0; i < droppedUrlCnt; i++) {
         QString localPath = droppedUrls[i].toLocalFile();
         QFileInfo fileInfo(localPath);
         if(fileInfo.isDir()) {
             backupForm = new BackupForm(this);
             backupForm->show();
             backupForm->setSourceText(fileInfo.absoluteFilePath());
             event->acceptProposedAction();
         }
     }

}

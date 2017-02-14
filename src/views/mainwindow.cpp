#include "mainwindow.h"
#include "authdialog.h"

#include <QtGui>
#include <QMessageBox>

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
    if(backupForm)
        delete backupForm;
    if(userForm)
        delete userForm;
    close();
}

void MainWindow::initBackupList(){

    for(std::map<std::string,std::string> info : UsersBackupController::getInstance().getUsersBackupInfoList())
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
    userForm->setModal(true);
    userForm->show();
}

void MainWindow::on_actionDeconnexion_triggered(){
    AuthDialog authDialog;
    authDialog.show();
    close();
    authDialog.exec();
}

void MainWindow::onBackupItemClicked(QListWidgetItem *backupItem){
//    qDebug() << *backupItem;
}

void MainWindow::onNewBackupAdded(std::map<std::string,std::string> backupInfo){
    addBackupItem(backupInfo);
    UsersBackupController::getInstance().createUsersBackup(backupInfo);
}


void MainWindow::onBackupUpdated(std::map<std::string,std::string> backupInfo){

    UsersBackupController::getInstance().updateUsersBackup(backupInfo);
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
//    QListWidgetItem *item = backupList->currentItem();

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

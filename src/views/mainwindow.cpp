#include "mainwindow.h"
#include "authdialog.h"

#include <QtGui>
#include <QMessageBox>

UsersBackupsController MainWindow::userBcController = UsersBackupsController::getInstance();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    newBackupButton->setAcceptDrops(true);
    userBcController.setUser(UserController::getInstance().getCurrentUserLogin());
}

MainWindow::~MainWindow(){
    if(backupForm)
        delete backupForm;
    if(userForm)
        delete userForm;
    close();
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

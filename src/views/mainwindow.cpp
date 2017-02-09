#include "mainwindow.h"
#include <QtGui>
#include <QMessageBox>

UsersBackupsController MainWindow::userBcController = UsersBackupsController::getInstance();

MainWindow::MainWindow(std::string user, QWidget *parent) :
    QMainWindow(parent)
{
    userBcController.setUser(user);
    setupUi(this);
    newBackupButton->setAcceptDrops(true);
}

MainWindow::~MainWindow(){
    delete backupForm;
}


void MainWindow::on_newBackupButton_clicked(){
    backupForm = new FormSauvegarde(this);
    backupForm->show();
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
             backupForm = new FormSauvegarde(this);
             backupForm->show();
             backupForm->setSourceText(fileInfo.absoluteFilePath());
             event->acceptProposedAction();
         }
     }

}

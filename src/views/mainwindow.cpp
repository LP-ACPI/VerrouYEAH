#include "mainwindow.h"
#include <QtGui>
UsersBackupsController MainWindow::userBcController = UsersBackupsController::getInstance();

MainWindow::MainWindow(std::string user, QWidget *parent) :
    QMainWindow(parent)
{
    userBcController.setUser(user);
    setupUi(this);
    newBackupButton->acceptDrops();
}

MainWindow::~MainWindow()
{}


void MainWindow::on_newBackupButton_clicked(){
    FormSauvegarde *fenetreBackup = new FormSauvegarde(this);
    fenetreBackup->show();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls()){
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();

        FormSauvegarde *fenetreBackup = new FormSauvegarde(this);
        fenetreBackup->show();
        fenetreBackup->setSourceText(event->mimeData()->text());
    }
}

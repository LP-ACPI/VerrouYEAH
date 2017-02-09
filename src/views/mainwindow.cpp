#include "mainwindow.h"

UsersBackupsController MainWindow::userBcController = UsersBackupsController::getInstance();

MainWindow::MainWindow(std::string user, QWidget *parent) :
    QMainWindow(parent)
{
    userBcController.setUser(user);
    setupUi(this);
}

MainWindow::~MainWindow()
{}


void MainWindow::on_newBackupButton_clicked(){
    fBackup = new FormSauvegarde(this);
    fBackup->show();
}

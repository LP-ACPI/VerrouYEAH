#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "backupform.h"
#include "userform.h"
#include "../controllers/UsersBackupsController.h"
#include <QMainWindow>

class MainWindow :
        public QMainWindow,
        private Ui::HomeWindow
{
    Q_OBJECT

    static UsersBackupsController userBcController;

    BackupForm *backupForm;
    UserForm *userForm;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
signals:


protected slots:
    void on_newBackupButton_clicked();
    void on_actionUtilisateur_triggered();
    void on_actionDeconnexion_triggered();
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_homewindow.h"
#include "formsauvegarde.h"
#include "../controllers/UsersBackupsController.h"
#include <QMainWindow>

class MainWindow :
        public QMainWindow,
        private Ui::HomeWindow
{
    Q_OBJECT

    static UsersBackupsController userBcController;
    FormSauvegarde *fBackup;
public:
    explicit MainWindow(std::string,QWidget *parent = 0);
    ~MainWindow();
signals:

protected slots:
    void on_newBackupButton_clicked();

};

#endif // MAINWINDOW_H

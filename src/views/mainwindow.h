#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "formsauvegarde.h"
#include "../controllers/UsersBackupsController.h"
#include <QMainWindow>

class MainWindow :
        public QMainWindow,
        private Ui::HomeWindow
{
    Q_OBJECT

    static UsersBackupsController userBcController;
    FormSauvegarde *backupForm;
public:
    explicit MainWindow(std::string,QWidget *parent = 0);
    ~MainWindow();

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
signals:


protected slots:
    void on_newBackupButton_clicked();

};

#endif // MAINWINDOW_H

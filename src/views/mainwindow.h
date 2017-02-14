#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "backupform.h"
#include "userform.h"
#include "backupwidget.h"
#include "../controllers/UsersBackupController.h"
#include <QMainWindow>

class MainWindow :
        public QMainWindow,
        private Ui::HomeWindow
{
    Q_OBJECT

    static UsersBackupController userBcController;

    QList<BackupWidget*> backupWidgetList;
    BackupForm *backupForm;
    UserForm *userForm;
    void addBackupItem(std::map<std::string,std::string>);
    void initBackupList();

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

    void onBackupItemClicked(QListWidgetItem*);
    void onNewBackupAdded(std::map<std::string,std::string>);
    void onBackupUpdated(std::map<std::string,std::string>);
    void onBackupDeleted(std::string);
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "backupform.h"
#include "userform.h"
#include "backupwidget.h"
#include "backupdetailsdialog.h"

#include "../controllers/UsersBackupController.h"
#include <QMainWindow>

class MainWindow :
        public QMainWindow,
        private Ui::HomeWindow
{
    Q_OBJECT

    QList<BackupWidget*> backupWidgetList;
    BackupDetailsDialog *detailBakcupDialog;
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
    void itemSelected();

protected slots:
    void on_newBackupButton_clicked();
    void on_actionUtilisateur_triggered();
    void on_actionDeconnexion_triggered();

    void onBackupItemClicked(QListWidgetItem*);
    void onBackupDeleted(std::string);
    void onBackupAdd(std::map<std::string,std::string>);
};

#endif // MAINWINDOW_H

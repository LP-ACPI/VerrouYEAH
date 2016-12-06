#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H
#include "ui_homewindow.h"
#include "authdialogwindow.h"
#include "backupformwindow.h"
#include <QMainWindow>
#include "backupitemwidget.h"
#include "configmanager.h"


class HomeWindow : public QMainWindow, private Ui::HomeWindow
{
    Q_OBJECT
private:
    BackupFormWindow *bcFormWin;
    ConfigManager *confMan;
    AuthDialogWindow *athWin;

public:
    explicit HomeWindow(QWidget *parent = 0);
    ~HomeWindow();

    ConfigManager* getConfig() const;
    void listBackups();
    void addBackup(Backup&);
    void modifBackup(Backup &);
    void removeBackup(Backup&);

protected slots:
    void on_newBackupButton_clicked();
    void onBackupItemClicked(QListWidgetItem*);
    void on_actionRAZ_triggered();
};

#endif // HOMEWINDOW_H

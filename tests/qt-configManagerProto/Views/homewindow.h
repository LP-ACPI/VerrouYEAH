#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H
#include <QMainWindow>
#include "ui_homewindow.h"
#include "backupformwindow.h"
#include "configmanager.h"


class HomeWindow : public QMainWindow, private Ui::HomeWindow
{
    Q_OBJECT
private:
    BackupFormWindow *bcFormWin;
    ConfigManager *confMan;

public:
    explicit HomeWindow(QWidget *parent = 0);
    ~HomeWindow();

    ConfigManager* getConfig() const;
    void refresh();
    void addBackup(Backup&);
    void modifBackup(Backup &);
    void removeBackup(Backup&);

protected slots:
    void on_newBackupButton_clicked();
    void on_actionRAZ_triggered();
    void onBackupItemClicked(QListWidgetItem*);
    void onBackupFormWindowAccepted();
};

#endif // HOMEWINDOW_H

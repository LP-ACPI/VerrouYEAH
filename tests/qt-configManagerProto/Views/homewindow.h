#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H
#include <QMainWindow>
#include <QProgressDialog>
#include "ui_homewindow.h"
#include "backupformwindow.h"
#include "configmanager.h"


class HomeWindow : public QMainWindow, private Ui::HomeWindow
{
    Q_OBJECT
private:
    BackupFormWindow *bcFormWin;
    ConfigManager *confMan;
    QProgressDialog *cryptProgress;

public:
    explicit HomeWindow(QWidget *parent = 0);
    ~HomeWindow();

    ConfigManager* getConfig() const;
    void refresh();
    void addBackup(Backup&);
    void modifBackup(Backup &);
    void removeBackup(Backup&);
signals:
    bool cryptingDone();

protected slots:
    void on_newBackupButton_clicked();
    void on_actionRAZ_triggered();
    void onBackupItemClicked(QListWidgetItem*);
    void onBackupFormWindowAccepted(Backup*);
    void cryptingProgress(quint64,quint64);
};

#endif // HOMEWINDOW_H

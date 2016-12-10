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
    void modifBackup(Backup &,Backup &);
    void removeBackup(Backup&);

signals:
    //signaux à émettre selon telle ou telle action
    bool cryptingStart(Backup *);
    bool cryptingDone();

protected slots:
    //slots "intelligents" de Qt -> connexion gérée par Qt au signal correspondant
    void on_newBackupButton_clicked();
    void on_actionRAZ_triggered();
    void on_actionUtilisateur_triggered();

    //slots du développeur --> connexion à établir (cf .cpp)
    void onBackupItemClicked(QListWidgetItem*);

    void cryptingProgress(quint64,quint64);  //pour la barre de progression - évolution du cryptage (émission du signal cf.:ConfigManager::cryptDirWithCount)
    void onCryptingStart(Backup *);                //action à effectuer au début du cryptage
    void onCryptingDone();                                //action à effectuer à la fin du cryptage

    void on_action_propos_triggered();
};

#endif // HOMEWINDOW_H

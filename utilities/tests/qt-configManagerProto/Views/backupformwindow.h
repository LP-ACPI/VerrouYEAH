#ifndef ADDBACKUPWINDOW_H
#define ADDBACKUPWINDOW_H

#include "ui_backupform.h"
#include "Entities/backup.h"
#include <QDialog>

class BackupFormWindow : public QDialog, private Ui::BackupForm
{
    Q_OBJECT
private:
    std::string flag;
    Backup *backup;

public:
    explicit BackupFormWindow(QWidget *parent = 0);
    explicit BackupFormWindow(Backup*, QWidget *parent = 0);
    ~BackupFormWindow();


protected slots:
    //slots "intelligents" de Qt -> connexion gérée par Qt au signal correspondant
    void on_newBackupButtonBox_accepted(); //action à effectuer au clic sur "OK"
    void on_newBackupButtonBox_rejected();   //action à effectuer au clic sur "Annuler"
    void on_srcDirChoose_clicked();                      //action à effectuer au clic sur "choisir la source"
    void on_trgDirChoose_clicked();                      //action à effectuer au clic sur "choisir la cible"
};

#endif // ADDBACKUP_H

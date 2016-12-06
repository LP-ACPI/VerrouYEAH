#ifndef ADDBACKUPWINDOW_H
#define ADDBACKUPWINDOW_H

#include "ui_backupform.h"
#include <QDialog>
#include <Entities/backup.h>

class BackupFormWindow : public QDialog, private Ui::BackupForm
{
    Q_OBJECT
private:
    std::string flag;

public:
    explicit BackupFormWindow(QWidget *parent = 0);
    explicit BackupFormWindow(Backup*, QWidget *parent = 0);
    ~BackupFormWindow();

protected slots:
    void on_newBackupButtonBox_accepted();
    void on_newBackupButtonBox_rejected();
    void on_srcDirChoose_clicked();
    void on_trgDirChoose_clicked();
};

#endif // ADDBACKUP_H

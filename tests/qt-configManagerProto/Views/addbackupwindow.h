#ifndef ADDBACKUPWINDOW_H
#define ADDBACKUPWINDOW_H

#include "ui_addnewbackup.h"
#include <QDialog>

class AddBackupWindow : public QDialog, private Ui::AddNewBackup
{
    Q_OBJECT
private:

public:
    explicit AddBackupWindow(QWidget *parent = 0);
    ~AddBackupWindow();

protected slots:
    void on_newBackupButtonBox_accepted();
    void on_newBackupButtonBox_rejected();
    void on_srcDirChoose_clicked();
    void on_trgDirChoose_clicked();
};

#endif // ADDBACKUP_H

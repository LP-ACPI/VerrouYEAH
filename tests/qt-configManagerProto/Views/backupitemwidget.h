#ifndef BACKUPITEMWIDGET_H
#define BACKUPITEMWIDGET_H
#include "backupitemwidget.h"
#include "ui_backupwidget.h"

#include <Entities/backup.h>


class BackupItemWidget : public QWidget, private Ui::BackupWidget
{
    Q_OBJECT
private:
    Backup *bc;

public:
    BackupItemWidget(QWidget *parent = 0);
    BackupItemWidget(Backup*,QWidget *parent = 0);
    ~BackupItemWidget();

    Backup* getBackup() const;
    void setBackup(Backup*) ;

protected slots:
    void on_trashButton_clicked();

};

#endif // BACKUPITEMWIDGET_H

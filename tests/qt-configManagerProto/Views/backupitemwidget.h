#ifndef BACKUPITEMWIDGET_H
#define BACKUPITEMWIDGET_H
#include "ui_backupwidget.h"
#include "homewindow.h"
#include "Entities/backup.h"


class BackupItemWidget : public QWidget, private Ui::BackupWidget
{
    Q_OBJECT
private:
    HomeWindow *_parent;
    Backup *bc;

public:
    BackupItemWidget(QWidget *parent = 0);
    BackupItemWidget(Backup*,QWidget *parent = 0);
    ~BackupItemWidget();

    Backup* getBackup() const;
    void setBackup(Backup*) ;

protected slots:
    void on_trashButton_pressed();

};

#endif // BACKUPITEMWIDGET_H

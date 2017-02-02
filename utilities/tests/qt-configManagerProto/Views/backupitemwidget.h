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

protected:
    QPoint dragStartPosition;
    void mouseMoveEvent(QMouseEvent*);

public:
    BackupItemWidget(QWidget *parent = 0);
    BackupItemWidget(Backup*,QWidget *parent = 0);
    ~BackupItemWidget();

    Backup* getBackup() const;
    void setBackup(Backup*) ;

    void restartPos();

signals:
    void droppedOut(QDropEvent*,Backup*);

protected slots:
    //slots "intelligent" de Qt -> connexion gérée par Qt au signal correspondant
    void on_trashButton_pressed();
    void on_decryptButton_pressed();

};

#endif // BACKUPITEMWIDGET_H

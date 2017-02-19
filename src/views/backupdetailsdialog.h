#ifndef DETAILSSAUVEGARDE_H
#define DETAILSSAUVEGARDE_H

#include "ui_backupdetailsdialog.h"
#include <QDialog>
#include <QFileSystemModel>
#include "backupwidget.h"

class BackupDetailsDialog : public  QDialog, private Ui::BackupDetailsDialog
{
    Q_OBJECT

    QWidget _parent;
    QFileSystemModel *model ;

public:
    explicit BackupDetailsDialog(std::string, QWidget *parent = 0);
    ~BackupDetailsDialog();

private:

};

#endif // DETAILSSAUVEGARDE_H

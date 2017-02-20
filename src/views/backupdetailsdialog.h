#ifndef DETAILSSAUVEGARDE_H
#define DETAILSSAUVEGARDE_H

#include "ui_backupdetailsdialog.h"
#include "../services/Observer.h"
#include <QDialog>
#include <QFileSystemModel>
#include "backupwidget.h"

class BackupDetailsDialog : public  QDialog, private Ui::BackupDetailsDialog, public Observer
{
    Q_OBJECT

    QWidget _parent;
    QFileSystemModel *model ;
    std::string backupKey;
    std::string targetId;

    virtual void update(nlohmann::json) const override;

public:
    explicit BackupDetailsDialog(std::string, QWidget *parent = 0);
    ~BackupDetailsDialog();

private:

};

#endif // DETAILSSAUVEGARDE_H

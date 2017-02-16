#ifndef DETAILSSAUVEGARDE_H
#define DETAILSSAUVEGARDE_H

#include <QDialog>
#include <QListWidget>
#include "backupwidget.h"

namespace Ui {
class DetailsSauvegarde;
}

class DetailsSauvegarde : public  QDialog
{
    Q_OBJECT

public:
    explicit DetailsSauvegarde(QWidget *parent = 0,  BackupWidget *backupItem = 0);
    ~DetailsSauvegarde();

private:
    Ui::DetailsSauvegarde *ui;
};

#endif // DETAILSSAUVEGARDE_H

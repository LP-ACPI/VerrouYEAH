#ifndef DETAILSSAUVEGARDE_H
#define DETAILSSAUVEGARDE_H

#include "ui_detailssauvegarde.h"
#include <QDialog>
#include <QListWidget>
#include "backupwidget.h"

class DetailsSauvegarde : public  QDialog, private Ui::DetailsSauvegarde
{
    Q_OBJECT

    QWidget _parent;

public:
    explicit DetailsSauvegarde(std::string, QWidget *parent = 0);
    ~DetailsSauvegarde();

private:

};

#endif // DETAILSSAUVEGARDE_H

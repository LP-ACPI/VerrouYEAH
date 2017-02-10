#ifndef FORMSAUVEGARDE_H
#define FORMSAUVEGARDE_H

#include "ui_backupformdialog.h"
#include <QDialog>

class BackupForm : public QDialog, private Ui::BackupFormDialog
{
    Q_OBJECT

public:
    explicit BackupForm(QWidget *parent = 0);
    ~BackupForm();
    void setSourceText(QString);

private:
};

#endif // FORMSAUVEGARDE_H

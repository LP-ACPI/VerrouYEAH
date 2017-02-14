#ifndef FORMSAUVEGARDE_H
#define FORMSAUVEGARDE_H

#include "ui_backupformdialog.h"
#include <QDialog>

class BackupForm : public QDialog, private Ui::BackupFormDialog
{
    Q_OBJECT
    std::string _backupKey;

    void init();
public:
    explicit BackupForm(QWidget *parent = 0);
    explicit BackupForm(std::string backupKey, QWidget *parent = 0);

    ~BackupForm();
    void setSourceText(QString);

signals:
    void newBackupAdded(std::map<std::string,std::string>);
    void BackupUpdated(std::map<std::string,std::string>);

protected slots:
    void on_backupButtonBox_accepted();
    void on_backupButtonBox_rejected();
};

#endif // FORMSAUVEGARDE_H

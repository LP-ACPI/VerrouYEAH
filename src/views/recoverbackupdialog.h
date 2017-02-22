#ifndef RECOVERBACKUPDIALOG_H
#define RECOVERBACKUPDIALOG_H

#include "ui_recoverbackupsdialog.h"
#include "targetchoicedialog.h"
#include <QDialog>

class RecoverBackupsDialog : public QDialog, private Ui::RecoverBackupsDialog
{
    Q_OBJECT
    TargetChoiceDialog *targetChoice;
    bool isFormValid();
public:
    explicit RecoverBackupsDialog(QWidget *parent =0);
    RecoverBackupsDialog();

    ~RecoverBackupsDialog();
signals:
    void postData(std::string,std::string,std::string);
    void researchFinished(QString);
    void addFoundData(std::map<std::string,std::string>);

protected slots:
    void on_targetChoiceButton_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void startResearchBackup(std::string,std::string,std::string);
    void onTargetSelected(QString);
};

#endif // RECOVERBACKUPDIALOG_H

#ifndef FORMSAUVEGARDE_H
#define FORMSAUVEGARDE_H

#include "ui_backupformdialog.h"
#include "progressdialog.h"
#include "targetchoicedialog.h"
#include "frequencyform.h"

#include <QDialog>

class BackupForm : public QDialog, private Ui::BackupFormDialog
{
    Q_OBJECT
    std::string _backupKey;
    ProgressDialog *progressDialog;
    TargetChoiceDialog* targetChoice;
    FrequencyForm* frequencyForm;

    std::map<std::string,std::string> backup_info;

    bool isFormValid();
    void init();
public:
    explicit BackupForm(QWidget *parent = 0);
    explicit BackupForm(std::string backupKey, QWidget *parent = 0);

    ~BackupForm(){
        if(progressDialog)
            delete progressDialog;
        if(targetChoice)
            delete targetChoice;
    }

    void setSourceText(QString);

signals:
    void postCreateBackupData(std::map<std::string,std::string>);
    void postUpdateBackupData(std::map<std::string,std::string>);
    void addNewBackup(std::map<std::string,std::string>);

protected slots:
    void on_backupButtonBox_accepted();
    void on_backupButtonBox_rejected();

    void on_sourceChoiceButton_clicked();
    void on_targetChoiceButton_clicked();

    void onNewBackupAdded(std::map<std::string,std::string>);
    void onBackupUpdated(std::map<std::string,std::string>);
    void onTargetSelected(QString);

private slots:
    void on_FrequencyButton_clicked();
    void onFrequencySelected(QString);
};

#endif // FORMSAUVEGARDE_H

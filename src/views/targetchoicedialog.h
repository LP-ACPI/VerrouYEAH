#ifndef TARGETCHOICEDIALOG_H
#define TARGETCHOICEDIALOG_H

#include "ui_targetchoicedialog.h"
#include "targetformdialog.h"
#include <QDialog>

class TargetChoiceDialog : public QDialog, private Ui::TargetChoiceDialog
{
    Q_OBJECT

    TargetFormDialog *targFormDialog;

    void refreshTargetChoice();
    void removeFtpTarget(QString);
    void removeNormalTarget(QString);

public:
    explicit TargetChoiceDialog(QWidget *parent = 0);
    QStringList ftpTagList;
    QStringList normalTagList;

    ~TargetChoiceDialog(){
        if(targFormDialog)
            delete targFormDialog;
    }

signals:
    void targetSelected(QString);

public slots:
    void onTypeChoiceChanged(int);

    void on_addTarget_clicked();
    void on_configTarget_clicked();
    void on_removeTarget_clicked();

    void onFtpTargetUpdate();
    void onNormalTargetUpdate();


    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // TARGETCHOICEDIALOG_H

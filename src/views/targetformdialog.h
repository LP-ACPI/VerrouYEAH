#ifndef NEWTARGETDIALOG_H
#define NEWTARGETDIALOG_H

#include "ui_targetformdialog.h"
#include <QDialog>

class TargetFormDialog : public QDialog, private Ui::TargetFormDialog
{
    Q_OBJECT
    bool createNotUpdate;
    bool isFtpFormValid();
    bool isNormalFormValid();
    bool isNotValid();
    std::string _targetTag;
public:
    explicit TargetFormDialog(QWidget *parent = 0);
    explicit TargetFormDialog(std::string, QWidget *parent = 0);

    void setCurrentTargetType(QString);

signals:
    void postFtpTargetData(std::map<std::string,std::string>);
    void postNormalTargetData(std::map<std::string,std::string>);
    void ftpTargetChange();
    void normalTargetChange();

public slots:
    void refreshLayout(QString);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_dirChoice_clicked();

    void onNewNormalTargetAdd(std::map<std::string,std::string>);
    void onNormalTargetUpdate(std::map<std::string,std::string>);

    void onNewFtpTargetAdd(std::map<std::string,std::string>);
    void onFtpTargetUpdate(std::map<std::string,std::string>);
};

#endif // NEWTARGETDIALOG_H

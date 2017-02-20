#include "backupdetailsdialog.h"
#include "ui_backupdetailsdialog.h"
#include "../controllers/BackupController.h"
#include "../controllers/UsersBackupController.h"
#include "../controllers/TargetController.h"
#include "filesystemmodel.h"
#include <QDebug>

BackupDetailsDialog::BackupDetailsDialog(std::string _backupKey, QWidget *parent) :
     QDialog(parent),_parent(parent), backupKey(_backupKey)
{
    setupUi(this);

    BackupController::getInstance().subscribeObserverToBackup(this,backupKey);
    std::map<std::string,std::string> backupInfo = UsersBackupController::getInstance().getUsersBackupInfo(backupKey);
    std::map<std::string,std::string> targetInfo;

    nameLabel->setText(QString::fromStdString(backupInfo["name"]));
    sourcePathLabel->setText(QString::fromStdString(backupInfo["source_path"]));
    frequencyLabel->setText(QString::fromStdString(backupInfo["frequency"]));
    lastSaveLabel->setText(QString::fromStdString(backupInfo["last_save"]));

    QPixmap state_icon;
    QString targetPath;
    targetId = backupInfo["target_id"];

    if(BackupController::getInstance().isBackupFtp(backupKey)){
        targetInfo = TargetController::getInstance().favoriteFtpTargetToInfoMap(targetId);
        targetHostLabel->setText(QString::fromStdString(targetInfo["host"]) );
        targetPath ="/"+ QString::fromStdString(targetInfo["path"]);
        if(backupInfo["data_loaded"] == "oui")
            state_icon = QPixmap(":/images/cloud-ok.png");
        else
            state_icon = QPixmap(":/images/cloud-ko.png");

   } else {
        targetInfo = TargetController::getInstance().favoriteNormalTargetToInfoMap(targetId);
        targetPath = QString::fromStdString(targetInfo["path"]);
        targetHostLabel->hide();

        if(backupInfo["data_loaded"] == "oui")
                state_icon = QPixmap(":/images/usb-ok.png");
            else
                state_icon = QPixmap(":/images/usb-ko.png");
    }

    stateIcon->setScaledContents(true);
    stateIcon->setPixmap(state_icon);

    targetNameLabel->setText(QString::fromStdString(targetInfo["tag"]));
    targetPathLabel->setText(targetPath);

    QString sourcePath = QString::fromStdString(backupInfo["source_path"])+"/";
    model = new FileSystemModel(this);
    model->setRootPath(sourcePath);
    model->setFilter(QDir::NoDotAndDotDot |
                     QDir::Dirs | QDir::Files | QDir::Hidden
    );
    treeView->setModel(model);
    treeView->setRootIndex(model->index(sourcePath));
}


BackupDetailsDialog::~BackupDetailsDialog()
{
    delete model;
    BackupController::getInstance().unsubscribeObserverFromBackup(this,backupKey);
    close();
}

void BackupDetailsDialog::update(nlohmann::json backupInfo) const{

}

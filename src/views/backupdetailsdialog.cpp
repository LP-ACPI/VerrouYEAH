#include "backupdetailsdialog.h"
#include "ui_backupdetailsdialog.h"
#include "../controllers/BackupController.h"
#include "../controllers/UsersBackupController.h"
#include "../controllers/TargetController.h"
#include "filesystemmodel.h"
#include "QJsonModel.h"
#include <QDebug>

BackupDetailsDialog::BackupDetailsDialog(std::string backupKey, QWidget *parent) :
     QDialog(parent),_parent(parent)
{
    setupUi(this);

    std::map<std::string,std::string> backupInfo = UsersBackupController::getInstance().getUsersBackupInfo(backupKey);
    std::map<std::string,std::string> targetInfo;

//Non: on est en MVC : pas d'objet de classe métier dans une view
 //   + y a déjà toutes les infos dans backupInfo et plus bas dans targetInfo

//    const Backup backup = BackupController::getInstance().getBackupFromInfoMap(info);
//    label_7->setText(QString::fromStdString(backup.getLastSave()));
   /* std::__cxx11::string targetType = backup.getTargetType();
    if (targetType.compare(std::string("NORMAL"))){
        //TODO : si cle disponible image ok sinon image disconnect
        QPixmap logoUSB(":/images/usb_connect.png");
        ui->label_8->setPixmap(logoUSB);
    } */

    nameLabel->setText(QString::fromStdString(backupInfo["name"]));
    sourcePathLabel->setText(QString::fromStdString(backupInfo["source_path"]));
    std::string targetType = TargetController::getInstance().getFavoriteTargetsType(backupInfo["target_id"]);

    QPixmap state_icon;
    QString targetPath;

    if(targetType == "FTP"){
        targetInfo = TargetController::getInstance().favoriteFtpTargetToInfoMap(backupInfo["target_id"]);
        targetHostLabel->setText(QString::fromStdString(targetInfo["host"]) );
        targetPath ="/"+ QString::fromStdString(targetInfo["path"]);
        if(backupInfo["data_loaded"] == "oui")
            state_icon = QPixmap(":/images/cloud-ok.png");
        else
            state_icon = QPixmap(":/images/cloud-ko.png");

   } else {
        targetInfo = TargetController::getInstance().favoriteNormalTargetToInfoMap(backupInfo["target_id"]);
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

    //Récup des data nécéssaire avant
    //debug json:
    QString sourcePath = QString::fromStdString(backupInfo["source_path"])+"/";
    model = new FileSystemModel(this);
    model->setRootPath(sourcePath);
    model->setFilter(QDir::NoDotAndDotDot |
                     QDir::Dirs | QDir::Files | QDir::Hidden
    );
    treeView->setModel(model);
    treeView->setRootIndex(model->index(sourcePath));

//    json jsonBackupData = BackupController::getInstance().getJsonifiedDataTree(backupKey);
//    if(jsonBackupData != NULL) {
//        std::string json_data = jsonBackupData.dump(2);
//        QByteArray byte_array(json_data.c_str(), json_data.length());
//        QJsonModel * model = new QJsonModel;
//        model->loadJson(byte_array);
//    } else {

//    }
    //backupItem->
    //il manque :
    // prendre les informations sur la planification et treeView avec l'arborescence

}

BackupDetailsDialog::~BackupDetailsDialog()
{
    delete model;
    close();
}

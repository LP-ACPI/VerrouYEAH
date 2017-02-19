#include "backupdetailsdialog.h"
#include "ui_backupdetailsdialog.h"
#include "../controllers/BackupController.h"
#include "../controllers/UsersBackupController.h"
#include "../controllers/TargetController.h"
#include <QDirModel>
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
    if(targetType == "FTP")
        targetInfo = TargetController::getInstance().favoriteFtpTargetToInfoMap(backupInfo["target_id"]);
    else
        targetInfo = TargetController::getInstance().favoriteNormalTargetToInfoMap(backupInfo["target_id"]);


    targetPathLabel->setText(QString::fromStdString(targetInfo["path"]));

    //Récup des data nécéssaire avant
    //debug json:

    json jsonBackupData = BackupController::getInstance().getJsonifiedDataTree(backupKey);
    if(jsonBackupData != NULL) {
        std::string json_data = jsonBackupData.dump(2);
        QByteArray byte_array(json_data.c_str(), json_data.length());
        QJsonModel * model = new QJsonModel;
        treeView->setModel(model);
        model->loadJson(byte_array);
    } else {

    }
    //backupItem->
    //il manque :
    // prendre les informations sur la planification et treeView avec l'arborescence

}

BackupDetailsDialog::~BackupDetailsDialog()
{
    close();
}

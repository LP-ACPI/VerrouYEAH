#include "backupdetailsdialog.h"
#include "ui_backupdetailsdialog.h"
#include "../controllers/BackupController.h"
#include "../controllers/UsersBackupController.h"
#include <QDirModel>
#include "QJsonModel.h"
#include <QDebug>

BackupDetailsDialog::BackupDetailsDialog(std::string backupKey, QWidget *parent) :
     QDialog(parent),_parent(parent)
{
    setupUi(this);

    std::map<std::string,std::string> infoMap = UsersBackupController::getInstance().getUsersBackupInfo(backupKey);


    //TODO : Bug Data est toujours vide
    /*const Data* data = BackupController::getInstance().getData(cle);
    QJsonModel* model = new QJsonModel;
    ui->treeView->setModel(model);
    model->loadJson(QByteArray::fromStdString(data->to_json()));*/



//Non: on est en MVC : pas de d'objet de classe métier dans une view
 //   + y a déjà toutes les infos dans infoMap
//    const Backup backup = BackupController::getInstance().getBackupFromInfoMap(info);
//    label_7->setText(QString::fromStdString(backup.getLastSave()));
   /* std::__cxx11::string targetType = backup.getTargetType();
    if (targetType.compare(std::string("NORMAL"))){
        //TODO : si cle disponible image ok sinon image disconnect
        QPixmap logoUSB(":/images/usb_connect.png");
        ui->label_8->setPixmap(logoUSB);
    } */

    nameLabel->setText(QString::fromStdString(infoMap["name"]));
    sourcePathLabel->setText(QString::fromStdString(infoMap["source_path"]));
    targetPathLabel->setText(QString::fromStdString(infoMap["target_path"]));


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

#include "detailssauvegarde.h"
#include "ui_detailssauvegarde.h"
#include "../controllers/BackupController.h"
#include "../controllers/UsersBackupController.h"
#include <QDirModel>
#include "QJsonModel.h"
#include <QDebug>

DetailsSauvegarde::DetailsSauvegarde(std::string backupKey, QWidget *parent) :
     QDialog(parent),_parent(parent)
{
    setupUi(this);

    std::map<std::string,std::string> info = UsersBackupController::getInstance().getUsersBackupInfo(backupKey);


    //TODO : Bug Data est toujours vide
    /*const Data* data = BackupController::getInstance().getData(cle);
    QJsonModel* model = new QJsonModel;
    ui->treeView->setModel(model);
    model->loadJson(QByteArray::fromStdString(data->to_json()));*/




    const Backup backup = BackupController::getInstance().getBackupFromInfoMap(info);
    label_7->setText(QString::fromStdString(backup.getLastSave()));
   /* std::__cxx11::string targetType = backup.getTargetType();
    if (targetType.compare(std::string("NORMAL"))){
        //TODO : si cle disponible image ok sinon image disconnect
        QPixmap logoUSB(":/images/usb_connect.png");
        ui->label_8->setPixmap(logoUSB);
    } */

    nameLabel->setText(QString::fromStdString(info["name"]));
    sourcePathLabel->setText(QString::fromStdString(info["source_path"]));

    targetPathLabel->setText(QString::fromStdString(info["target_path"]));


    //Récup des data nécéssaire avant
    //debug json:

    std::string json_data = BackupController::getInstance().getJsonifiedDataTree(backupKey);
    QByteArray byte_array(json_data.c_str(), json_data.length());
    QJsonModel * model = new QJsonModel;
    treeView->setModel(model);
    model->loadJson(byte_array);
    //backupItem->
    //il manque :
    // prendre les informations sur la planification et treeView avec l'arborescence

}

DetailsSauvegarde::~DetailsSauvegarde()
{
    close();
}

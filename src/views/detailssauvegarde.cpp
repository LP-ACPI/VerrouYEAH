#include "detailssauvegarde.h"
#include "ui_detailssauvegarde.h"
#include "../controllers/BackupController.h"
#include "../controllers/UsersBackupController.h"
#include "QJsonModel.h"
#include <QDebug>

DetailsSauvegarde::DetailsSauvegarde(std::string backupKey, QWidget *parent) :
     QDialog(parent),_parent(parent)
{
    setupUi(this);

    std::map<std::string,std::string> info = UsersBackupController::getInstance().getUsersBackupInfo(backupKey);

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

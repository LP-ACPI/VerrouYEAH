#include "detailssauvegarde.h"
#include "ui_detailssauvegarde.h"
#include "../controllers/UsersBackupController.h"
#include <QDirModel>

DetailsSauvegarde::DetailsSauvegarde(QWidget *parent,  BackupWidget *backupItem) :
     QDialog(parent),
    ui(new Ui::DetailsSauvegarde)
{
    ui->setupUi(this);

    std::string cle = backupItem->getBackupKey();
    std::map<std::string,std::string> info = UsersBackupController::getInstance().getUsersBackupInfo(cle);

    ui->label->setText(QString::fromStdString(info["name"]));
    ui->label_3->setText(QString::fromStdString(info["source_path"]));

    ui->label_2->setText(QString::fromStdString(info["target_path"]));

    QDirModel *modele = new QDirModel;
    ui->treeView->setModel(modele);
    //backupItem->
    //il manque :
    // prendre les informations sur la planification et treeView avec l'arborescence
}

DetailsSauvegarde::~DetailsSauvegarde()
{
    delete ui;
}

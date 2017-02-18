#include "detailssauvegarde.h"
#include "ui_detailssauvegarde.h"
#include "../controllers/UsersBackupController.h"
#include <QDirModel>
#include "../controllers/backupcontroller.h"
#include "../models/qjsonmodel.h"

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


    //TODO : Bug Data est toujours vide
    /*const Data* data = BackupController::getInstance().getData(cle);
    QJsonModel* model = new QJsonModel;
    ui->treeView->setModel(model);
    model->loadJson(QByteArray::fromStdString(data->to_json()));*/




    const Backup backup = BackupController::getInstance().getBackupFromInfoMap(info);
    ui->label_7->setText(QString::fromStdString(backup.getLastSave()));
    std::__cxx11::string targetType = backup.getTargetType();
    if (targetType.compare(std::string("NORMAL"))){
        //TODO : si cle disponible image ok sinon image disconnect
        QPixmap logoUSB(":/images/usb_connect.png");
        ui->label_8->setPixmap(logoUSB);
    }
}

DetailsSauvegarde::~DetailsSauvegarde()
{
    delete ui;
}

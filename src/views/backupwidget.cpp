#include "backupwidget.h"
#include "backupform.h"
#include "progressdialog.h"
#include "../controllers/BackupController.h"
#include "../controllers/TargetController.h"
#include "../controllers/UsersBackupController.h"
#include <QFileIconProvider>
#include <QMessageBox>

BackupWidget::BackupWidget(QWidget *parent) : QWidget(parent),_parent(parent)
{
    setupUi(this);
}

void BackupWidget::setBackupInfo(std::map<std::string,std::string> backupInfo){
    backupKey = backupInfo["key"];

    BackupController::getInstance().subscribeObserverToBackup(this,backupKey);

    backupName->setText(QString::fromStdString(backupInfo["name"]));
    backupSource->setText(QString::fromStdString(backupInfo["source_path"]));
    QPixmap state_icon;

    if(BackupController::getInstance().isBackupFtp(backupKey)){
        targetInfo = TargetController::getInstance().favoriteFtpTargetToInfoMap(backupInfo["target_id"]);

        if(backupInfo["data_loaded"] == "oui")
            state_icon = QPixmap(":/images/cloud-ok.png");
        else
            state_icon = QPixmap(":/images/cloud-ko.png");

    }else{
        targetInfo = TargetController::getInstance().favoriteNormalTargetToInfoMap(backupInfo["target_id"]);

        if(backupInfo["data_loaded"] == "oui")
            state_icon = QPixmap(":/images/usb-ok.png");
        else
            state_icon = QPixmap(":/images/usb-ko.png");
    }

    stateIcon->setScaledContents(true);
    stateIcon->setPixmap(state_icon);

    backupTarget->setText(QString::fromStdString(targetInfo["tag"]));

    QString tool_tip_text = "<b>Nom: </b> "+ QString::fromStdString(backupInfo["name"])+
                                          "<br/><b>destination:</b>"+QString::fromStdString(targetInfo["tag"])+
                                            "<br/>est accessible : " +QString::fromStdString(backupInfo["data_loaded"]);

    setToolTip(tool_tip_text);

}

void BackupWidget::on_trashButton_clicked(){
    int response = QMessageBox::warning(this, "Attention!",
       "Vous allez supprimer votre sauvegarde<br/><b>"
                          +backupName->text()
                          +"</b><br/>Etes-vous sûr?",
                 QMessageBox::Yes | QMessageBox::No);

    if(response == QMessageBox::Yes)
         emit removed(backupKey);
}

void BackupWidget::on_configButton_clicked(){
    BackupForm *backupForm = new BackupForm(backupKey,_parent);
    backupForm->show();

    connect(backupForm,SIGNAL(postUpdateBackupData(std::map<std::string,std::string>)),
            this,SLOT(onBackupUpdated(std::map<std::string,std::string>)));
}

void BackupWidget::on_decryptButton_clicked(){
    ProgressDialog *progressDialog = new ProgressDialog(_parent);
    progressDialog->setFtp(targetInfo["type"] == "FTP");
    progressDialog->setUpload(false);
    progressDialog->init();
    progressDialog->show();
    BackupController::getInstance().restoreBackupData(backupKey);
}

void BackupWidget::onBackupUpdated(std::map<std::string,std::string> backupInfo){
        setBackupInfo(backupInfo);
}

void BackupWidget::update(nlohmann::json backup)  {
    try{
        std::map<std::string,std::string> bc_map;
         bc_map["key"]                  = backup["key"];
        bc_map["name"]               =backup["name"];
        bc_map["source_path"] =backup["src"];
        bc_map["last_save"]       = backup["last_save"];
        bc_map["note"]                = backup["note"];
        bc_map["frequency"]     = backup["freq"];
        bc_map["target_id"]        =TargetController::getInstance().targetCouplesTagKey()[backup["dest"]["tag"]];
        bc_map["data_loaded"] = BackupController::getInstance().hasBackupLoadedData( bc_map["key"]  ) ? "oui" : "non";
        setBackupInfo(bc_map);
    }catch(std::domain_error &e){}
}

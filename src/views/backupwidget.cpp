#include "backupwidget.h"
#include "backupform.h"
#include "progressdialog.h"
#include "../controllers/BackupController.h"
#include "../controllers/UserController.h"
#include "../controllers/TargetController.h"
#include "../controllers/UsersBackupController.h"
#include <QFileIconProvider>
#include <QMessageBox>

BackupWidget::BackupWidget(std::string _backupKey,QWidget *parent)
    : QWidget(parent),backupKey(_backupKey), _parent(parent)
{
    setupUi(this);
}

void BackupWidget::subscribeToBackup(){
    BackupController::getInstance().subscribeObserverToBackup(this,backupKey);
}

void BackupWidget::setBackupInfo(std::map<std::string,std::string> backupInfo){

    std::string saveName = backupInfo["name"];
    std::string userName =  UserController::getInstance().getCurrentUserLogin();

    backupName->setText(QString::fromStdString(saveName));
    backupSource->setText(QString::fromStdString(backupInfo["source_path"]));
    QPixmap state_icon;

    if(BackupController::getInstance().isBackupFtp(backupKey)){
        targetInfo = TargetController::getInstance().favoriteFtpTargetToInfoMap(backupInfo["target_tag"]);

        if(backupInfo["data_loaded"] == "oui")
            state_icon = QPixmap(":/images/cloud-ok.png");
        else
            state_icon = QPixmap(":/images/cloud-ko.png");

    }else{
        targetInfo = TargetController::getInstance().favoriteNormalTargetToInfoMap(backupInfo["target_tag"]);

        if(backupInfo["data_loaded"] == "oui")
            state_icon = QPixmap(":/images/usb-ok.png");
        else
            state_icon = QPixmap(":/images/usb-ko.png");
    }

    stateIcon->setScaledContents(true);
    stateIcon->setPixmap(state_icon);

    configButton->setToolTip("Configuration de votre sauvegarde. "
                             "\nEn cas de modification de la destination, l'ancienne saugarde est toujours à la précédente");
    decryptButton->setToolTip("Décrypter vers 'decrypt/"+
                           QString::fromStdString(saveName) +"_"+
                             QString::fromStdString(userName)+"'");
    trashButton->setToolTip("Supprimer votre sauvegarde : "
                            "\nannule la sauvegarde automatique. "
                            "\nPour la supprimer définitivement, supprimez '"+
                            QString::fromStdString(saveName)+".vy'"+
                                                   " et le '"+ QString::fromStdString(userName)+".config' associés");
    backupTarget->setText(QString::fromStdString(targetInfo["tag"]));

    QString tool_tip_text = "<b>Nom: </b> "+ QString::fromStdString(saveName)+
            "<br/><b>source:</b> "+QString::fromStdString(backupInfo["source_path"])+
            "<br/><b>destination:</b> "+QString::fromStdString(targetInfo["tag"])+
            "<br/><b>fréquence:</b> "+QString::fromStdString(backupInfo["frequency"])+
            "<br/><b>dernière sauvegarde:</b> "+QString::fromStdString(backupInfo["last_save"])+
            "<br/><b>est accessible :</b> " +QString::fromStdString(backupInfo["data_loaded"])+
            "<br/><b>note :</b> " +QString::fromStdString(backupInfo["note"]);

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
    if(BackupController::getInstance().servicesAreBusy()){
        QMessageBox::warning(this, "Attention!",
                             "les services sont actuellement occupés à effectuer une sauvegarde. "
                             "\nMerci de reéssayer plus tard");
        return;
    }
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
        bc_map["target_tag"]    =backup["dest"]["tag"];
        bc_map["data_loaded"] = BackupController::getInstance().hasBackupLoadedData( bc_map["key"]  ) ? "oui" : "non";
        setBackupInfo(bc_map);
        qDebug()<< QString::fromStdString(bc_map["name"]);
    }catch(std::domain_error &e){}
}

#include "backupform.h"
#include "../controllers/UsersBackupController.h"
#include "../controllers/TargetController.h"
#include <QFileDialog>
#include <QFileIconProvider>
#include <QMessageBox>
#include <QStyle>
#include <QDateTime>
#include <QDebug>

BackupForm::BackupForm(QWidget *parent) :
    QDialog(parent),_backupKey("null")
{   
    init();

    connect(this,SIGNAL(postCreateBackupData(std::map<std::string,std::string>)),
            this,SLOT(onNewBackupAdded(std::map<std::string,std::string>)));

    connect(this,SIGNAL(addNewBackup(std::map<std::string,std::string>)),
            parent,SLOT(onBackupAdd(std::map<std::string,std::string>)));

    setWindowTitle("Nouvelle Sauvegarde");
}

BackupForm::BackupForm(std::string backupKey, QWidget *parent) :
    QDialog(parent),_backupKey(backupKey)
{
    init();

     backup_info = UsersBackupController::getInstance().getUsersBackupInfo(backupKey);

    std::string targetTag;
    backup_info["target_type"] = TargetController::getInstance().getFavoriteTargetsType(backup_info["target_id"]);
    if(backup_info["target_type"]  == "FTP")
        targetTag = TargetController::getInstance().favoriteFtpTargetToInfoMap(backup_info["target_id"])["tag"];
   else
        targetTag = TargetController::getInstance().favoriteNormalTargetToInfoMap(backup_info["target_id"])["tag"];

    sourceChoiceButton->setText(QString::fromStdString(backup_info["source_path"]));
    noteInput->setPlainText(QString::fromStdString(backup_info["note"]));
    nameInput->setText(QString::fromStdString(backup_info["name"]));
    targetChoiceButton->setText(QString::fromStdString(targetTag));

    connect(this,SIGNAL(postUpdateBackupData(std::map<std::string,std::string>)),
            this,SLOT(onBackupUpdated(std::map<std::string,std::string>)));

    setWindowTitle("Modification de "+nameInput->text());

}

void BackupForm::init(){
    setupUi(this);
    setModal(true);
    progressDialog = new ProgressDialog(this);
    targetChoice = new TargetChoiceDialog(this);
    frequencyForm = new FrequencyForm(this);

    icon->setPixmap(QFileIconProvider().icon(QFileIconProvider::File).pixmap(30,30));
    sourceIcon->setPixmap(QFileIconProvider().icon(QFileIconProvider::Folder).pixmap(25,25));
    targetIcon->setPixmap(style()->standardIcon(QStyle::SP_DialogSaveButton).pixmap(25,25));
}

void BackupForm::setSourceText(QString sourcePath){
    sourceChoiceButton->setText(sourcePath);
    sourceChoiceButton->setToolTip(sourcePath);
}


void BackupForm::on_backupButtonBox_accepted(){

    if(!isFormValid())
        return;

    backup_info["name"]         = nameInput->text().toStdString();
    backup_info["source_path"]  = sourceChoiceButton->text().toStdString();
    //TODO - destination favorites d'utilisateur + form
    backup_info["target_tag"]  = targetChoiceButton->text().toStdString();

    backup_info["note"]         = noteInput->toPlainText().toStdString();

    //TODO - lastSave : DateTime
    QDateTime date_time;
    backup_info["last_save"] = date_time.currentDateTime().toString().toStdString();
    //TODO - implém fréquence + form
//    backup_info["frequency"] = "*-*-*-*-*";

    hide();
    if(_backupKey == "null"){
        emit postCreateBackupData(backup_info);
    } else {
        backup_info["key"] = _backupKey;
        emit postUpdateBackupData(backup_info);
    }
}

void BackupForm::on_backupButtonBox_rejected(){
    close();
}

void BackupForm::onNewBackupAdded(std::map<std::string,std::string> backupInfo){
    //TODO : verif si FTP/NORMAL + Upload

    progressDialog->setFtp(backup_info["target_type"]  == "FTP");
    progressDialog->setUpload(true);
    progressDialog->init();
    progressDialog->show();

    std::map<std::string,std::string> bc_info_wth_key
            = UsersBackupController::getInstance().addNewUsersBackup(backupInfo);
    emit addNewBackup(bc_info_wth_key);
}


void BackupForm::onBackupUpdated(std::map<std::string,std::string> backupInfo){
    progressDialog = new ProgressDialog(this);
    //TODO : verif si FTP/NORMAL + Upload
    progressDialog->setFtp(backup_info["target_type"]  == "FTP");
    progressDialog->setUpload(true);
    progressDialog->init();
    progressDialog->show();
    UsersBackupController::getInstance().updateUsersBackup(backupInfo);
}

bool BackupForm::isFormValid(){
    bool empty_entries = sourceChoiceButton->text().isEmpty()
            || nameInput->text().isEmpty()
            || targetChoiceButton->text().isEmpty();

    if(empty_entries){
        QMessageBox::warning(this, "Attention!",
          "Merci de remplir toutes les informations");
      return false;
    }
    return true;
}

void BackupForm::on_sourceChoiceButton_clicked(){
    QString sourceDir = QFileDialog::getExistingDirectory();
    sourceChoiceButton->setText(sourceDir);
    sourceChoiceButton->setToolTip(sourceDir);
}

void BackupForm::on_targetChoiceButton_clicked(){
    targetChoice->show();
    connect(targetChoice,SIGNAL(targetSelected(QString)),this,SLOT(onTargetSelected(QString)));
}

void BackupForm::onTargetSelected(QString targetTag){
    targetChoiceButton->setText(targetTag);
    targetChoiceButton->setToolTip(targetTag);
    backup_info["target_type"] = TargetController::getInstance().getFavoriteTargetsType( backup_info["target_id"] );
}

void BackupForm::on_FrequencyButton_clicked(){
    frequencyForm->show();
    connect(frequencyForm,SIGNAL(frequencySelected(QString)),this,SLOT(onFrequencySelected(QString)));
}

void BackupForm::onFrequencySelected(QString frequencyTag){

}

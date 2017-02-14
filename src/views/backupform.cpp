#include "backupform.h"
#include "ui_backupformdialog.h"
#include "../controllers/UsersBackupController.h"
#include <QFileIconProvider>
#include <QStyle>
#include <QDebug>

BackupForm::BackupForm(QWidget *parent) :
    QDialog(parent),_backupKey("null")
{   
    init();

    connect(this,SIGNAL(newBackupAdded(std::map<std::string,std::string>)),
            parent,SLOT(onNewBackupAdded(std::map<std::string,std::string>)));
}

BackupForm::BackupForm(std::string backupKey, QWidget *parent) :
    QDialog(parent),_backupKey(backupKey)
{
    init();

    std::map<std::string,std::string> backup_info = UsersBackupController::getInstance().getUsersBackupInfo(backupKey);

    nameInput->setText(QString::fromStdString(backup_info["name"]));
    sourceInput->setText(QString::fromStdString(backup_info["source_path"]));
    targetInput->setText(QString::fromStdString(backup_info["target_path"]));
    noteInput->setPlainText(QString::fromStdString(backup_info["note"]));

    connect(this,SIGNAL(BackupUpdated(std::map<std::string,std::string>)),
            parent,SLOT(onBackupUpdated(std::map<std::string,std::string>)));


}

void BackupForm::init(){
    setupUi(this);
    icon->setPixmap(QFileIconProvider().icon(QFileIconProvider::Folder).pixmap(32,32));
    sourceChoiceButton->setIcon(QFileIconProvider().icon(QFileIconProvider::Folder));
    targetChoiceButton->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
}


BackupForm::~BackupForm()
{}

void BackupForm::setSourceText(QString sourcePath){
    sourceInput->setText(sourcePath);
    sourceInput->setToolTip(sourcePath);
}


void BackupForm::on_backupButtonBox_accepted(){

    std::map<std::string,std::string> backup_info;

    backup_info["name"]         = nameInput->text().toStdString();
    backup_info["source_path"]  = sourceInput->text().toStdString();
    //TODO - destination favorites d'utilisateur + form
    backup_info["target_path"]  = targetInput->text().toStdString();
    backup_info["target_type"]  = "NORMAL";
    backup_info["note"]         = noteInput->toPlainText().toStdString();

    //TODO - lastSave : DateTime
    QDateTime date_time;
    backup_info["last_save"] = date_time.currentDateTime().toString().toStdString();
    //TODO - implém fréquence + form
//    backup_info["frequency"] = "*-*-*-*-*";

    if(_backupKey == "null")
        emit newBackupAdded(backup_info);
    else {
        backup_info["key"] = _backupKey;
        emit BackupUpdated(backup_info);
    }

    close();
}

void BackupForm::on_backupButtonBox_rejected(){
    close();
}

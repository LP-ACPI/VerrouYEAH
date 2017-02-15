#include "backupwidget.h"
#include "backupform.h"
#include "../controllers/BackupController.h"
#include <QFileIconProvider>
#include <QDebug>

BackupWidget::BackupWidget(QWidget *parent) : QWidget(parent),_parent(parent)
{
    setupUi(this);

    QPixmap saveIcon(":/images/save-icon.png");
    icon->setScaledContents(true);
    icon->setPixmap(saveIcon);

    QIcon delButIcon(QPixmap(":/images/trash-icon.png"));
    trashButton->setIconSize(QSize(30,30));
    trashButton->setIcon(delButIcon);

    QIcon configButIcon(QPixmap(":/images/config-icon.png"));
    configButton->setIconSize(QSize(40,40));
    configButton->setIcon(configButIcon);

}

void BackupWidget::setBackupInfo(std::map<std::string,std::string> backupInfo){
    backupKey = backupInfo["key"];
    backupName->setText(QString::fromStdString(backupInfo["name"]));
    backupSource->setText(QString::fromStdString(backupInfo["source_path"]));
    backupTarget->setText(QString::fromStdString(backupInfo["target_path"]));
}

void BackupWidget::on_trashButton_clicked(){
    emit removed(backupKey);
}

void BackupWidget::on_configButton_clicked(){
    BackupForm *backupForm = new BackupForm(backupKey,_parent);
    backupForm->show();

    connect(backupForm,SIGNAL(BackupUpdated(std::map<std::string,std::string>)),
            this,SLOT(onBackupUpdated(std::map<std::string,std::string>)));
}

void BackupWidget::on_decryptButton_clicked(){
    BackupController::getInstance().decryptBackup(backupKey);
}


void BackupWidget::onBackupUpdated(std::map<std::string,std::string> backupInfo){
    backupName->setText(QString::fromStdString(backupInfo["name"]));
    backupSource->setText(QString::fromStdString(backupInfo["source_path"]));
    backupTarget->setText(QString::fromStdString(backupInfo["target_path"]));
}

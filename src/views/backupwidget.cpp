#include "backupwidget.h"
#include "backupform.h"
#include "progressdialog.h"
#include "../controllers/BackupController.h"
#include "../controllers/TargetController.h"
#include <QFileIconProvider>
#include <QMessageBox>

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
    backupTarget->setText(QString::fromStdString(backupInfo["target_tag"]));

    std::string targetType = TargetController::getInstance().getFavoriteTargetsType(backupInfo["target_id"]);
    if(targetType == "FTP")
        targetInfo = TargetController::getInstance().favoriteFtpTargetToInfoMap(backupInfo["target_id"]);
    else
        targetInfo = TargetController::getInstance().favoriteNormalTargetToInfoMap(backupInfo["target_id"]);

    QString tool_tip_text = "<b>Key: </b> "+ QString::fromStdString(backupKey)+
                                            "<br/><b>target:</b>"+QString::fromStdString(targetInfo["target_tag"])+
                                            "";


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
    progressDialog->init();
    progressDialog->show();
    BackupController::getInstance().restoreBackupData(backupKey);
}

void BackupWidget::onBackupUpdated(std::map<std::string,std::string> backupInfo){
        setBackupInfo(backupInfo);
}

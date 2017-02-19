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

    std::string targetType = TargetController::getInstance().getFavoriteTargetsType(backupInfo["target_id"]);
    if(targetType == "FTP")
        targetInfo = TargetController::getInstance().favoriteFtpTargetToInfoMap(backupInfo["target_id"]);
    else
        targetInfo = TargetController::getInstance().favoriteNormalTargetToInfoMap(backupInfo["target_id"]);

    backupTarget->setText("("+QString::fromStdString(targetType)+
                           ") "+QString::fromStdString(targetInfo["tag"]));

    QString tool_tip_text = "<b>Nom: </b> "+ QString::fromStdString(backupInfo["name"])+
                                          "<br/><b>destination:</b>("+QString::fromStdString(targetType)+
                                            ") "+QString::fromStdString(targetInfo["tag"])+
                                            "<br/>est accessible : " +QString::fromStdString(backupInfo["data_loaded"]);
   QPixmap state_icon;
    if(targetType == "FTP")
        if(backupInfo["data_loaded"] == "oui")
            state_icon = QPixmap(":/images/cloud-ok.png");
        else
            state_icon = QPixmap(":/images/cloud-ko.png");
    else
        if(backupInfo["data_loaded"] == "oui")
            state_icon = QPixmap(":/images/usb-ok.png");
        else
            state_icon = QPixmap(":/images/usb-ko.png");

    stateIcon->setScaledContents(true);
    stateIcon->setPixmap(state_icon);

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

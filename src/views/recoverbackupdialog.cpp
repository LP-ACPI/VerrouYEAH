#include "recoverbackupdialog.h"
#include "../controllers/UsersBackupController.h"
#include "../controllers/TargetController.h"
#include <QMessageBox>

RecoverBackupsDialog::RecoverBackupsDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    connect(this,SIGNAL(postData(std::string,std::string,std::string)),this,SLOT(startResearchBackup(std::string,std::string,std::string)));
 }

RecoverBackupsDialog::~RecoverBackupsDialog(){
    if(targetChoice)
        delete targetChoice;
}

void RecoverBackupsDialog::on_targetChoiceButton_clicked(){
    targetChoice = new TargetChoiceDialog(this);
    targetChoice->show();
    connect(targetChoice,SIGNAL(targetSelected(QString)),this,SLOT(onTargetSelected(QString)));
}

void RecoverBackupsDialog::on_buttonBox_accepted(){
    if(!isFormValid())
        return;

    std::string target_id = TargetController::getInstance().targetCouplesTagKey()[targetChoiceButton->text().toStdString()];
    std::string login = loginInput->text().toStdString();
    std::string pass  = passInput->text().toStdString();

    emit postData(login,pass,target_id);
}

void RecoverBackupsDialog::on_buttonBox_rejected(){
    close();
}

void RecoverBackupsDialog::startResearchBackup(std::string  login,std::string  pass,std::string targetId){
    try {
        nlohmann::json backups;
        backups = UsersBackupController::getInstance().recoverUsersNonRegistrededBackups(login,pass,targetId);
    } catch(const std::exception &e){
        QMessageBox::warning(this, "Attention!",
          QString::fromStdString(e.what()));
      return;
    }
}

bool RecoverBackupsDialog::isFormValid(){
    bool empty_fields = targetChoiceButton->text() == "destination"
            || passInput->text().isEmpty()
            || loginInput->text().isEmpty();

    if(empty_fields){
        QMessageBox::warning(this, "Attention!",
          "Merci de remplir tous les champs");
      return false;
    }
    return true;
}

void RecoverBackupsDialog::onTargetSelected(QString target){
    targetChoiceButton->setText(target);
}

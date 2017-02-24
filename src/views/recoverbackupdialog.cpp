#include "recoverbackupdialog.h"
#include "../controllers/UsersBackupController.h"
#include "../controllers/TargetController.h"
#include <QMessageBox>
#include <QProgressDialog>

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

    std::string target_tag = targetChoiceButton->text().toStdString();
    std::string login = loginInput->text().toStdString();
    std::string pass  = passInput->text().toStdString();

    emit postData(login,pass,target_tag);
}

void RecoverBackupsDialog::on_buttonBox_rejected(){
    close();
}

void RecoverBackupsDialog::startResearchBackup(std::string  login,std::string  pass,std::string targetTag){

    QProgressDialog *waitDialog = new QProgressDialog(this);
    waitDialog->setWindowTitle("Merci de patienter durant la récupération...");
    waitDialog->setMaximum(0);
    waitDialog->setMinimum(0);
    waitDialog->setMinimumWidth(200);
    waitDialog->show();

    try {

        nlohmann::json found_backups;
        found_backups = UsersBackupController::getInstance()
                .recoverUsersNonRegistrededBackups(login,pass,targetTag);

        QStringList foundBackupNames;
        QStringList existingBackupNames;

        for(json backup : found_backups["found"] ){

            foundBackupNames.append(QString::fromStdString(backup["name"]));

            std::map<std::string,std::string> bc_map
                    = UsersBackupController::getInstance().getUsersBackupInfo(backup["key"]);

            emit addFoundData(bc_map);
        }

        for(json backup : found_backups["exist"] ){
            existingBackupNames.append(QString::fromStdString(backup["name"]));
        }


        QString resultMessage =
                "Les sauvegardes suivantes ont été récupérées: \n\n"+
                foundBackupNames.join("\n");
        emit researchFinished(resultMessage);

        if(existingBackupNames.size()>0)
            QMessageBox::warning(this, "Résultat des recherches",
                                 " Les sauvegardes suivantes sont en conflit avec les vôtres: <br/><br/>"
                                 "<b>"+existingBackupNames.join("<br/>")+
                                 "</b> <br/> Veuillez les renommer avent une nouvelle tentative.");

    } catch(const std::exception &e){
        QMessageBox::warning(this, "Attention!",
          QString::fromStdString(e.what()));
    }

    delete waitDialog;
    close();
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

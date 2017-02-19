#include "targetchoicedialog.h"
#include "../controllers/TargetController.h"
#include <QFileIconProvider>
#include <QMessageBox>
#include <qdebug.h>

TargetChoiceDialog::TargetChoiceDialog(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    setWindowTitle("Choix de destination");


    for(std::string ftp_tag : TargetController::getInstance().listFavoriteFtpTargetTags())
        ftpTagList.append(QString::fromStdString(ftp_tag));

    for(std::string normal_tag : TargetController::getInstance().listlFavoriteNormalTargetTags())
        normalTagList.append(QString::fromStdString(normal_tag));

    connect(typeChoice,SIGNAL(currentIndexChanged(int)),this,SLOT(onTypeChoiceChanged(int)));

    tagChoice->addItems(normalTagList);
    refreshTargetChoice();
}

void TargetChoiceDialog::refreshTargetChoice(){

    tagChoice->clear();
    if(typeChoice->currentText() == "FTP")
        tagChoice->addItems(ftpTagList);
    else
        tagChoice->addItems(normalTagList);

    if(tagChoice->count() == 0){
        configTarget->setDisabled(true);
        removeTarget->setDisabled(true);
    } else {
        configTarget->setDisabled(false);
        removeTarget->setDisabled(false);
    }
}

void TargetChoiceDialog::removeFtpTarget(QString ftpTag){
    ftpTagList.removeOne(ftpTag);
    refreshTargetChoice();
}


void TargetChoiceDialog::removeNormalTarget(QString  normalTag){
    normalTagList.removeOne(normalTag);
    refreshTargetChoice();
}


void TargetChoiceDialog::onTypeChoiceChanged(int){
    refreshTargetChoice();
}

void TargetChoiceDialog::on_addTarget_clicked(){
    targFormDialog = new TargetFormDialog(this);
    targFormDialog->show();
    targFormDialog->setCurrentTargetType(typeChoice->currentText());

    connect(targFormDialog,SIGNAL(ftpTargetChange()),this,SLOT(onFtpTargetUpdate()));
    connect(targFormDialog,SIGNAL(normalTargetChange()),this,SLOT(onNormalTargetUpdate()));
}

void TargetChoiceDialog::on_configTarget_clicked(){
    std::string tag = tagChoice->currentText().toStdString();
    std::string key = TargetController::getInstance().targetCouplesTagKey()[tag];
    targFormDialog = new TargetFormDialog(key,this);
    targFormDialog->show();

    if(typeChoice->currentText() == "FTP")
        connect(targFormDialog,SIGNAL(ftpTargetChange()),this,SLOT(onFtpTargetUpdate()));
    else
        connect(targFormDialog,SIGNAL(normalTargetChange()),this,SLOT(onNormalTargetUpdate()));
}
void TargetChoiceDialog::onFtpTargetUpdate(){

    ftpTagList.clear();
    for(std::string ftp_tag : TargetController::getInstance().listFavoriteFtpTargetTags())
        ftpTagList.append(QString::fromStdString(ftp_tag));

    if(typeChoice->currentText() == "FTP")
        refreshTargetChoice();
}

void TargetChoiceDialog::onNormalTargetUpdate(){
    normalTagList.clear();
    for(std::string normal_tag : TargetController::getInstance().listlFavoriteNormalTargetTags())
        normalTagList.append(QString::fromStdString(normal_tag));

    if(typeChoice->currentText() == "NORMAL")
         refreshTargetChoice();
}

void TargetChoiceDialog::on_removeTarget_clicked(){
   int response = QMessageBox::warning(this, "Attention!",
      "Vous allez supprimer votre destination "
                         +tagChoice->currentText()
                         +"\nEtes-vous sûr?",
                QMessageBox::Yes|QMessageBox::No);

   if(response == QMessageBox::Yes){

       std::string tag = tagChoice->currentText().toStdString();
       std::string key = TargetController::getInstance().targetCouplesTagKey()[tag];
       TargetController::getInstance().deleteFavoriteTarget(key);

       if(typeChoice->currentText() == "FTP")
           removeFtpTarget(tagChoice->currentText());
       else
           removeNormalTarget(tagChoice->currentText());
   }
}

void TargetChoiceDialog::on_buttonBox_accepted(){
         emit targetSelected(tagChoice->currentText());
        close();
}

void TargetChoiceDialog::on_buttonBox_rejected(){
         close();
}

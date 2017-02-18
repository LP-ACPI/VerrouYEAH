#include "targetformdialog.h"
#include "../controllers/TargetController.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

TargetFormDialog::TargetFormDialog(QWidget *parent)
    : QDialog(parent), _targetId("null")
{
    setupUi(this);

    connect(typeChoice,SIGNAL(currentTextChanged(QString)),this,SLOT(refreshLayout(QString)));
    connect(this,SIGNAL(postFtpTargetData(std::map<std::string,std::string>)),
                                this,SLOT(onNewFtpTargetAdd(std::map<std::string,std::string>)));
    connect(this,SIGNAL(postNormalTargetData(std::map<std::string,std::string>)),
                                this,SLOT(onNewNormalTargetAdd(std::map<std::string,std::string>)));
}


TargetFormDialog::TargetFormDialog(std::string targetKey, QWidget *parent)
    : QDialog(parent),_targetId(targetKey)
{
    setupUi(this);

    QString targetType(QString::fromStdString(TargetController::getInstance().getFavoriteTargetsType(targetKey)));
    typeChoice->setCurrentText(targetType);
    typeChoice->setDisabled(true);
    refreshLayout(targetType);

    if(targetType == "FTP"){
        std::map<std::string,std::string> ftpTargetInfo = TargetController::getInstance().favoriteFtpTargetToInfoMap(targetKey);
        tagInput->setText(QString::fromStdString(ftpTargetInfo["tag"]));
        hostInput->setText(QString::fromStdString(ftpTargetInfo["host"]));
        usernameInput->setText(QString::fromStdString(ftpTargetInfo["username"]));
        passInput->setText(QString::fromStdString(ftpTargetInfo["pass"]));
        pathInput->setText(QString::fromStdString(ftpTargetInfo["path"]));        

        connect(this,SIGNAL(postFtpTargetData(std::map<std::string,std::string>)),
                                     this,SLOT(onFtpTargetUpdate(std::map<std::string,std::string>)));
   }     else {
        std::map<std::string,std::string> normalTargetInfo = TargetController::getInstance().favoriteNormalTargetToInfoMap(targetKey);
        tagInput->setText(QString::fromStdString(normalTargetInfo["tag"]));
        dirChoice->setText(QString::fromStdString(normalTargetInfo["path"]));

        connect(this,SIGNAL(postNormalTargetData(std::map<std::string,std::string>)),
                                    this,SLOT(onNormalTargetUpdate(std::map<std::string,std::string>)));
    }

}

void TargetFormDialog::refreshLayout(QString selectedType){
    if(selectedType == "FTP"){
        dirChoice->hide();
        hostInput->show();
        passInput->show();
        pathInput->show();
        usernameInput->show();
        setMinimumHeight(325);
        setMaximumHeight(325);
        buttonBox->move(buttonBox->pos().x(), 280);
    } else {
        usernameInput->hide();
        hostInput->hide();
        passInput->hide();
        pathInput->hide();
        dirChoice->show();
        setMinimumHeight(225);
        setMaximumHeight(225);
        buttonBox->move(buttonBox->pos().x(), 160);
    }
}

void TargetFormDialog::setCurrentTargetType(QString targetType){
    typeChoice->setCurrentText(targetType);
    refreshLayout(targetType);
}

void TargetFormDialog::on_buttonBox_accepted(){

    std::map<std::string,std::string> targetInfo;
    targetInfo["target_id"] = _targetId;
    targetInfo["tag"] = tagInput->text().toStdString();
    if(typeChoice->currentText()=="FTP")    {
        if(!isFtpFormValid())
            return;
        targetInfo["host"] = hostInput->text().toStdString();
        targetInfo["username"] = usernameInput->text().toStdString();
        targetInfo["path"] = pathInput->text().toStdString();
        emit postFtpTargetData(targetInfo);
    }    else   {
        if(!isNormalFormValid())
            return;
        targetInfo["path"] = dirChoice->text().toStdString();
        emit postNormalTargetData(targetInfo);
    }
    close();
}

void TargetFormDialog::on_buttonBox_rejected(){
    close();
}

void TargetFormDialog::on_dirChoice_clicked(){
    QString destDir = QFileDialog::getExistingDirectory();
    dirChoice->setText(destDir);
    dirChoice->setToolTip(destDir);
}


void TargetFormDialog::onNewNormalTargetAdd(std::map<std::string,std::string> targetInfo){

    TargetController::getInstance().addNewFavoriteNormalTarget(targetInfo);
    emit normalTargetChange();
}

void TargetFormDialog::onNormalTargetUpdate(std::map<std::string,std::string> targetInfo){
    TargetController::getInstance().updateFavoriteNormalTarget(targetInfo);
    emit normalTargetChange();
}

void TargetFormDialog::onNewFtpTargetAdd(std::map<std::string,std::string> targetInfo){
    TargetController::getInstance().addNewFavoriteFtpTarget(targetInfo);
    emit ftpTargetChange();
}

void TargetFormDialog::onFtpTargetUpdate(std::map<std::string,std::string> targetInfo){
    TargetController::getInstance().updateFavoriteFtpTarget(targetInfo);
    emit ftpTargetChange();

}

bool TargetFormDialog::isFtpFormValid(){
    bool emptyInputs =  tagInput->text().isEmpty();
    emptyInputs         |= hostInput->text().isEmpty();
    emptyInputs         |= usernameInput->text().isEmpty();
    emptyInputs         |= passInput->text().isEmpty();
    emptyInputs         |= pathInput->text().isEmpty();

    if(emptyInputs)
        return isNotValid();

    return true;
}

bool TargetFormDialog::isNormalFormValid(){
    bool emptyInputs =  tagInput->text().isEmpty()
            || dirChoice->text() == "chemin";

    if(emptyInputs)
        return isNotValid();
    return true;
}

bool TargetFormDialog::isNotValid(){
    QMessageBox::warning(this, "Attention!",
        "Merci de remplir toutes les informations");
    return false;
}

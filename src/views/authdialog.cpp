#include "authdialog.h"
#include "mainwindow.h"
#include "../controllers/UsersBackupsController.h"
#include <QMessageBox>
#include <QDebug>


UserController AuthDialog::userController = UserController::getInstance();


AuthDialog::AuthDialog(QWidget *parent):
    QDialog(parent)
{
    setupUi(this);

    userController.loadLoginsPassCouples();
    for(std::string login : userController.getLoginList())
        loginList->addItem(QString::fromStdString(login));

    QPixmap appLogo(":/images/logo_temporaire.png");
    logo->setScaledContents(true);
    logo->setPixmap(appLogo);

}

AuthDialog::~AuthDialog(){
    this->close();
}


void AuthDialog::on_authButtonBox_accepted(){
    std::string login = loginList->currentText().toStdString();
    std::string pass = userPassInput->text().toStdString();

    if(!userController.authentifyUser(login,pass)){
        QMessageBox::warning(this, "Attention!",
            "Erreur d'Authentification");
        return;
    }

    updateOrNotFavoriteUser(login);
    proceedToMainWindow(login);
}

void AuthDialog::on_authButtonBox_rejected(){
    this->close();
}

void AuthDialog::on_subscriptButtonBox_accepted(){
    std::string newLogin = newUserLoginInput->text().toStdString();
    std::string newPass = newUserPassInput->text().toStdString();
    std::string newPassConfirm = newUserPassInputConfirm->text().toStdString();

    bool emptyInputs = newUserLoginInput->text().isEmpty()
            || newUserPassInput->text().isEmpty();
    bool nonCorrespondingConfirm = newPass != newPassConfirm;

    bool isValid = validation(emptyInputs,nonCorrespondingConfirm);

    if(!isValid)
        return;

    if(!userController.createUser(newLogin,newPass)){
        QMessageBox::warning(this, "Nouvel Utilisateur",
                "l'utilisateur existe déjà !");
        return;
    }

    QString login = newUserLoginInput->text();
    loginList->addItem(login);

    int reponse = QMessageBox::question(this, "Nouvel Utilisateur",
                 "Nouvel utilisateur '"+ login +"' créé avec succés.\n"
                    "Continuer en tant que '"+ login +"'?",
                    QMessageBox ::Yes | QMessageBox::No
    );

    if(reponse ==  QMessageBox ::Yes)
        proceedToMainWindow(newLogin);

}

bool AuthDialog::validation(bool emptyInputs,bool nonCorrespondingConfirm){
    if(emptyInputs){
        QMessageBox::warning(this, "Attention!",
            "Merci de remplir toutes les informations");
        return false;
    }

    if(nonCorrespondingConfirm){
        QMessageBox::warning(this, "Attention!",
            "Les mots de passe ne correspondent pas!");
        return false;
    }
    return true;
}

void AuthDialog::updateOrNotFavoriteUser(std::string userLogin){
    if(favoriteUser->isChecked())
        userController.setFavoriteUser(userLogin);
    else userController.unsetFavoriteUser();
}

void AuthDialog::on_subscriptButtonBox_rejected(){
    this->close();
}

void AuthDialog::proceedToMainWindow(std::string login){
    MainWindow *mainWindow = new MainWindow(login);
    mainWindow->show();
    this->close();
}

#include "authdialog.h"
#include "mainwindow.h"
#include "../controllers/UsersBackupController.h"
#include <QMessageBox>
#include <QDebug>



AuthDialog::AuthDialog(QWidget *parent):
    QDialog(parent)
{
    setupUi(this);
    for(std::string login : UserController::getInstance().getLoginList())
        loginList->addItem(QString::fromStdString(login));

    connect(loginList,SIGNAL(currentTextChanged(QString)),this,SLOT(onLoginListChanged(QString)));

    QString auto_login_user = QString::fromStdString( UserController::getInstance().getFavoriteUser() );
    bool isAutoLogin = loginList->count()==0 ? false : loginList->currentText() == auto_login_user;

    autoLoginUserCheck->setChecked(isAutoLogin);
}

AuthDialog::~AuthDialog(){
    close();
}


void AuthDialog::on_authButtonBox_accepted(){
    std::string login = loginList->currentText().toStdString();
    std::string pass = userPassInput->text().toStdString();

    if(!UserController::getInstance().authentifyUser(login,pass)){
        QMessageBox::warning(this, "Attention!",
            "Erreur d'Authentification");
        return;
    }

    updateOrNotFavoriteUser(login);
    proceedToMainWindow(login);
}

void AuthDialog::on_authButtonBox_rejected(){
    close();
}

void AuthDialog::on_subscriptButtonBox_accepted(){
    std::string newLogin = newUserLoginInput->text().toStdString();
    std::string newPass = newUserPassInput->text().toStdString();

    if(!isFormValid())
        return;

    if(!UserController::getInstance().createUser(newLogin,newPass)){
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

void AuthDialog::on_subscriptButtonBox_rejected(){
    close();
}

void AuthDialog::onLoginListChanged(QString login){

    QString favoriteUser = QString::fromStdString( UserController::getInstance().getFavoriteUser() );

    bool isAutoLogin = login == favoriteUser;

    autoLoginUserCheck->setChecked(isAutoLogin);
}

bool AuthDialog::isFormValid(){
    std::string newPass = newUserPassInput->text().toStdString();
    std::string newPassConfirm = newUserPassInputConfirm->text().toStdString();

    bool emptyInputs = newUserLoginInput->text().isEmpty()
            || newUserPassInput->text().isEmpty();

    bool nonCorrespondingConfirm = newPass != newPassConfirm;
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
    if(autoLoginUserCheck->isChecked())
        UserController::getInstance().setFavoriteUser(userLogin);
    else
        UserController::getInstance().unsetFavoriteUser(userLogin);
}

void AuthDialog::proceedToMainWindow(std::string login){

    UserController::getInstance().setCurrentUser(login);
    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();
    close();
}



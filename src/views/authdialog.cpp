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

    connect(loginList,SIGNAL(currentTextChanged(QString)),this,SLOT(onLoginListChanged(QString)));

    QString auto_login_user = QString::fromStdString( userController.getFavoriteUser() );
    bool isAutoLogin = loginList->count()==0 ? false : loginList->currentText() == auto_login_user;

    autoLoginUserCheck->setChecked(isAutoLogin);
}

AuthDialog::~AuthDialog(){
    close();
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
    close();
}

void AuthDialog::on_subscriptButtonBox_accepted(){
    std::string newLogin = newUserLoginInput->text().toStdString();
    std::string newPass = newUserPassInput->text().toStdString();

    if(!isFormValid())
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

void AuthDialog::on_subscriptButtonBox_rejected(){
    close();
}

void AuthDialog::onLoginListChanged(QString login){

    bool isAutoLogin = login == QString::fromStdString( userController.getFavoriteUser() );

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
        userController.setFavoriteUser(userLogin);
    else
        userController.unsetFavoriteUser();
}

void AuthDialog::proceedToMainWindow(std::string login){
    userController.setCurrentUser(login);
    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();
    close();
}



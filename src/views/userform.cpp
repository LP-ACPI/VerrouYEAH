#include "userform.h"
#include "../controllers/UsersBackupsController.h"
#include <QMessageBox>
#include <QDebug>


UserController UserForm::userController = UserController::getInstance();

UserForm::UserForm(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    QString login = QString::fromStdString(userController.getCurrentUserLogin());

    bool isAutoLogin = login == QString::fromStdString( userController.getFavoriteUser() );

    userLoginInput->setText(login);
    userLogin->setText(login);

    autoLoginUserCheck->setChecked(isAutoLogin);
    QPixmap warnIcon(style()->standardIcon(QStyle::SP_MessageBoxWarning).pixmap(150,150));
    warningIcon->setScaledContents(true);
    warningIcon->setPixmap(warnIcon);

}

UserForm::~UserForm(){
    close();
}

void UserForm::on_updateUserButtonBox_accepted(){
    if(!isFormValid())
        return;

    std::string new_login = userLoginInput->text().toStdString();
    std::string new_pass =  userNewPassInput->text().toStdString();
    if(!userController.updateUser(new_login,new_pass)){
        QMessageBox::warning(this, "Mis à jour Utilisateur",
                "l'utilisateur existe déjà !");
        return;
    }

    QMessageBox::information(this, "Mise à jour",
                "Vous avez modifié vos informations\n"
                 "\nLogin: \t"+ userLoginInput->text()+
                 "\nMot de passe: \t"+ userNewPassInput->text()+
                  "\nConnexion auto: " + autoLoginUserCheck->isChecked(),
            QMessageBox ::Ok
        );
    close();


}

void UserForm::on_updateUserButtonBox_rejected(){
    close();
}

void UserForm::on_deleteUserButton_clicked(){
    close();
}

bool UserForm::isFormValid(){

    bool emptyInputs = userOldPassInput->text().isEmpty()
            || userNewPassInput->text().isEmpty()
            || userLoginInput->text().isEmpty();

    std::string oldPassEntered = userOldPassInput->text().toStdString();
    std::string old_login = userController.getCurrentUserLogin();

    bool nonCorrespondingOldPasses = userController.authentifyUser(old_login,oldPassEntered);

    if(emptyInputs){
        QMessageBox::warning(this, "Attention!",
            "Merci de remplir toutes les informations");
        return false;
    }

    if(nonCorrespondingOldPasses){
        QMessageBox::warning(this, "Attention!",
            "Ancien mot de passe ne correspond pas au mot de passe saisi!");
        return false;
    }
    return true;
}

void UserForm::updateOrNotFavoriteUser(std::string userLogin){
    if(autoLoginUserCheck->isChecked())
        userController.setFavoriteUser(userLogin);
    else {
        if(userController.favoriteUserExists())
            userController.unsetFavoriteUser();
    }
}

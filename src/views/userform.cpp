#include "userform.h"
#include "../controllers/UsersBackupController.h"
#include "authdialog.h"
#include <QMessageBox>

#include <QDebug>


UserForm::UserForm(QWidget *parent)
    : QDialog(parent), _parent(parent)
{
    setupUi(this);
    setModal(true);

    QString login = QString::fromStdString(UserController::getInstance().getCurrentUserLogin());

    bool isAutoLogin = login == QString::fromStdString( UserController::getInstance().getFavoriteUser() );

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

    if(fullUserUpdateIsNecessary())
        if(!updateUser())
            return;

    std::string new_login = userLoginInput->text().toStdString();
    updateOrNotFavoriteUser(new_login);
    close();
}

void UserForm::on_updateUserButtonBox_rejected(){
    close();
}

void UserForm::on_deleteUserButton_clicked(){
    int response = QMessageBox::warning(this, "Attention!",
                    "Vous allez supprimer votre compte."
                    "\nÊtes-sûrs de vouloir poursuivre?",
            QMessageBox::Yes | QMessageBox::No);

    if(response == QMessageBox::Yes ) {

        UserController::getInstance().deleteUser();

        close();
        _parent->close();

        AuthDialog authDialog;
        authDialog.show();
        authDialog.exec();
    }
    close();
}

bool UserForm::fullUserUpdateIsNecessary(){

    std::string old_login = UserController::getInstance().getCurrentUserLogin();
    std::string new_login = userLoginInput->text().toStdString();

    bool update_unnecessary =  userNewPassInput->text().isEmpty();
    update_unnecessary &= userOldPassInput->text().isEmpty();
    update_unnecessary &= (old_login == new_login);

    return !update_unnecessary;
}

bool UserForm::isFormValid(){

    std::string old_login = UserController::getInstance().getCurrentUserLogin();

    std::string entered_old_pass = userOldPassInput->text().toStdString();

    bool emptyInputs = userOldPassInput->text().isEmpty()
            || userNewPassInput->text().isEmpty()
            || userLoginInput->text().isEmpty();


    bool correspondingOldPasses = UserController::getInstance().authentifyUser(old_login,entered_old_pass);

    if(emptyInputs){
        QMessageBox::warning(this, "Attention!",
            "Merci de remplir toutes les informations");
        return false;
    }

    if(!correspondingOldPasses){
        QMessageBox::warning(this, "Attention!",
            "Ancien mot de passe ne correspond pas au mot de passe saisi!");
        return false;
    }
    return true;
}


bool UserForm::updateUser(){

    if(!isFormValid())
        return false;

    std::string new_login = userLoginInput->text().toStdString();
    std::string new_pass =  userNewPassInput->text().toStdString();

    if(!UserController::getInstance().updateUser(new_login,new_pass)){
        QMessageBox::warning(this, "Mise à jour Utilisateur",
                "l'utilisateur existe déjà !");
        return false;
    }

    QString info_auto_login =  autoLoginUserCheck->isChecked()? "Activé":"Désactivé";
    QMessageBox::information(this, "Mise à jour",
                "Vous avez modifié vos informations<br/>"
                 "<br/><b>Login:</b> "+ userLoginInput->text()+
                  "<br/><b>Mot de passe:</b> "+ userNewPassInput->text()+
                   "<br/><b>Connexion auto:</b> " + info_auto_login,
            QMessageBox ::Ok
        );

    return true;
}

void UserForm::updateOrNotFavoriteUser(std::string userLogin){
    if(autoLoginUserCheck->isChecked())
        UserController::getInstance().setFavoriteUser(userLogin);
    else
        UserController::getInstance().unsetFavoriteUser(userLogin);

}

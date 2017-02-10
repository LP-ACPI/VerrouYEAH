#include "userform.h"
#include "../controllers/UsersBackupsController.h"

UserController UserForm::userController = UserController::getInstance();

UserForm::UserForm(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    loginInput->setText(QString::fromStdString(userController.getCurrentUserLogin()));
    passInput->setText(QString::fromStdString(userController.getCurrentUserPass()));

}

UserForm::~UserForm(){

}

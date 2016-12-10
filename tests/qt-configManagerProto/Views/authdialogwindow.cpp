#include "authdialogwindow.h"
#include "Entities/user.h"
#include <QMessageBox>

//AuthDialogWindow::AuthDialogWindow(QWidget *parent) :
//    QDialog(parent)
//{
//    setupUi(this);
//}

AuthDialogWindow::AuthDialogWindow(ConfigManager *cm, QWidget *parent):
    QDialog(parent),
    _confMan(cm)
{
    setupUi(this);
    userNameInput->setText(cm->getUser()->getNom());
    userPassInput->setText(cm->getUser()->getMdp());
    setWindowTitle("Authentificaton!");
    setWindowIcon(QPixmap(":/images/LetsEncrypt_Logo.png"));
}

AuthDialogWindow::~AuthDialogWindow(){
    this->close();
}

void AuthDialogWindow::on_authButtonBox_accepted(){
    if(userNameInput->text().isEmpty()
            ||  userPassInput->text().isEmpty()) {

            if(QMessageBox::information(this, "Attention!",
                                        "Merci de remplir toutes les informations!"))
                return;
    }
     User u(userNameInput->text(), userPassInput->text());

    if(!_confMan->noUser()){
         u.setBackups(_confMan->getUser()->getBackups());
    }

    _confMan->setUser(u);
    _confMan->saveConfig();
    this->close();
}

void AuthDialogWindow::on_authButtonBox_rejected(){
    this->close();
}

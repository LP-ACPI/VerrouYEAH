#include "authdialogwindow.h"
#include "homewindow.h"
#include "Entities/user.h"
#include <QMessageBox>

AuthDialogWindow::AuthDialogWindow(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
}

AuthDialogWindow::~AuthDialogWindow(){
    this->destroy();
}

void AuthDialogWindow::on_authButtonBox_accepted(){
    if(userNameInput->text().isEmpty()
            ||  userPassInput->text().isEmpty()) {

            if(QMessageBox::information(this, "Attention!",
                                        "Merci de remplir toutes les informations!"))
                return;
    }

    HomeWindow* parent = qobject_cast<HomeWindow*>(this->parent());
    User u(userNameInput->text(), userPassInput->text());
    parent->getConfig()->setUser(u);
    parent->getConfig()->saveConfig();
    this->close();
}

void AuthDialogWindow::on_authButtonBox_rejected(){
    this->close();
}

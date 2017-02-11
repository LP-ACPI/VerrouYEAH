#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include "ui_authdialog.h"
#include "../controllers/UserController.h"
#include <QDialog>

class AuthDialog :
        public QDialog,
        private Ui::AuthDialog
{
    Q_OBJECT

    void updateOrNotFavoriteUser(std::string);
    bool isFormValid();
    void checkIfUserFound();

public:
    explicit AuthDialog(QWidget *parent = 0);
    ~AuthDialog();

    void proceedToMainWindow(std::string);

protected slots:
    void on_authButtonBox_accepted();
    void on_authButtonBox_rejected();

    void on_subscriptButtonBox_accepted();
    void on_subscriptButtonBox_rejected();

    void onLoginListChanged(QString);
};

#endif // AUTHDIALOG_H

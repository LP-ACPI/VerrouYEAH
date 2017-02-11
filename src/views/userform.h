#ifndef USERFORM_H
#define USERFORM_H

#include "ui_userformdialog.h"
#include "../controllers/UserController.h"
#include <QDialog>

class UserForm : public QDialog,
        private Ui::UserFormDialog
{
    Q_OBJECT
    static UserController userController;

    void updateOrNotFavoriteUser(std::string);
    bool isFormValid();

public:
    explicit UserForm(QWidget *parent = 0);
    ~UserForm();

protected slots:
    void on_updateUserButtonBox_accepted();
    void on_updateUserButtonBox_rejected();

    void on_deleteUserButton_clicked();

};

#endif // USERFORM_H

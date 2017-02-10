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

public:
    explicit UserForm(QWidget *parent = 0);
    ~UserForm();

};

#endif // USERFORM_H

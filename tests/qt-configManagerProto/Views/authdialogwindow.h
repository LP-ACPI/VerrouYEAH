#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include "ui_firstauthdialog.h"
#include "configmanager.h"
#include <QDialog>

class AuthDialogWindow : public QDialog, private Ui::AuthDialog
{
    Q_OBJECT

public:
    explicit AuthDialogWindow(QWidget *parent = 0);
    ~AuthDialogWindow();

protected slots:
    void on_authButtonBox_accepted();
    void on_authButtonBox_rejected();
};

#endif // AUTHDIALOG_H

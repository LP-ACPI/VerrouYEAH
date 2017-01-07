#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include "ui_firstauthdialog.h"
#include "configmanager.h"
#include <QDialog>

class AuthDialogWindow : public QDialog, private Ui::AuthDialog
{
    Q_OBJECT
private:
    ConfigManager *_confMan;
public:
//    explicit AuthDialogWindow(QWidget *parent = 0);
    explicit AuthDialogWindow(ConfigManager* ,QWidget *parent = 0);
    ~AuthDialogWindow();

protected slots:
    //slots "intelligents" de Qt -> connexion gérée par Qt au signal correspondant (par nom de du Widget dans UI)
    void on_authButtonBox_accepted(); // action à effectuer sur clic sur "OK"
    void on_authButtonBox_rejected();  // action à effectuer sur clic sur "Annuler"
};

#endif // AUTHDIALOG_H

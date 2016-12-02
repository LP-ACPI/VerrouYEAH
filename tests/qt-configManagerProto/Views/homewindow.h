#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H
#include "ui_homewindow.h"
#include <QMainWindow>

#include "addbackupwindow.h"

class HomeWindow : public QMainWindow, private Ui::HomeWindow
{
    Q_OBJECT

private:
    AddBackupWindow *add;

public:
    explicit HomeWindow(QWidget *parent = 0);
    ~HomeWindow();

protected slots:
    void on_newBackupButton_clicked();

};

#endif // HOMEWINDOW_H

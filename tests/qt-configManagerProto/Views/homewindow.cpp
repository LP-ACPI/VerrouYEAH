#include "homewindow.h"
#include "ui_homewindow.h"


HomeWindow::HomeWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

}

HomeWindow::~HomeWindow()
{
    this->destroy();
}

void HomeWindow::on_newBackupButton_clicked(){

    add = new AddBackupWindow;
    add->show();
}

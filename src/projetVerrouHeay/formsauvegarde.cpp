#include "formsauvegarde.h"
#include "ui_formsauvegarde.h"
#include <QFileIconProvider>
#include <QStyle>

FormSauvegarde::FormSauvegarde(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormSauvegarde)
{   
    ui->setupUi(this);
    ui->label->setPixmap(QFileIconProvider().icon(QFileIconProvider::Folder).pixmap(32,32));

    ui->pushButton->setIcon(QFileIconProvider().icon(QFileIconProvider::Folder));
    //QStyle style;
    ui->pushButton_2->setIcon(this->style()->standardIcon(QStyle::SP_DialogSaveButton));

}

FormSauvegarde::~FormSauvegarde()
{
    delete ui;
}

#include "formsauvegarde.h"
#include "ui_formsauvegarde.h"
#include <QFileIconProvider>
#include <QStyle>

FormSauvegarde::FormSauvegarde(QWidget *parent) :
    QDialog(parent)
{   
    setupUi(this);
    icon->setPixmap(QFileIconProvider().icon(QFileIconProvider::Folder).pixmap(32,32));

    sourceChoiceButton->setIcon(QFileIconProvider().icon(QFileIconProvider::Folder));
    //QStyle style;
    targetChoiceButton->setIcon(this->style()->standardIcon(QStyle::SP_DialogSaveButton));

}

FormSauvegarde::~FormSauvegarde()
{}

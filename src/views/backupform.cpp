#include "backupform.h"
#include "ui_backupformdialog.h"
#include <QFileIconProvider>
#include <QStyle>

BackupForm::BackupForm(QWidget *parent) :
    QDialog(parent)
{   
    setupUi(this);
    icon->setPixmap(QFileIconProvider().icon(QFileIconProvider::Folder).pixmap(32,32));

    sourceChoiceButton->setIcon(QFileIconProvider().icon(QFileIconProvider::Folder));
    //QStyle style;
    targetChoiceButton->setIcon(this->style()->standardIcon(QStyle::SP_DialogSaveButton));

}

BackupForm::~BackupForm()
{}

void BackupForm::setSourceText(QString cheminSource){
    sourceInput->setText(cheminSource);
    sourceInput->setToolTip(cheminSource);
}

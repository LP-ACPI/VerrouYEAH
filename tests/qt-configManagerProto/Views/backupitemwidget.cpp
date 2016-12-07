#include "backupitemwidget.h"
#include <QDebug>

BackupItemWidget::BackupItemWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    _parent = qobject_cast<HomeWindow*>(parent);

}


BackupItemWidget::BackupItemWidget(Backup *b,QWidget *parent) :
    QWidget(parent)
{
    bc = new Backup(*b);
    setupUi(this);
    BackupName->setText(bc->getName());
    BackupSource->setText(bc->getSource());
    BackupCible->setText(bc->getTarget());

   _parent = qobject_cast<HomeWindow*>(parent);

}

BackupItemWidget::~BackupItemWidget(){
    delete bc;
}

Backup* BackupItemWidget::getBackup() const {
    return bc;
}

void BackupItemWidget::setBackup( Backup *b) {
    BackupName->setText(b->getName());
    BackupSource->setText(b->getSource());
    BackupCible->setText(b->getTarget());
    bc->setName(b->getName());
    bc->setSource(b->getSource());
    bc->setTarget(b->getTarget());
}

void BackupItemWidget::on_trashButton_pressed(){

     //TODO
     _parent->removeBackup(*bc);
//

}



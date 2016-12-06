#include "backupitemwidget.h"
#include "homewindow.h"
#include <QDebug>

BackupItemWidget::BackupItemWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

}


BackupItemWidget::BackupItemWidget(Backup *b,QWidget *parent) :
    QWidget(parent)
{
    bc = new Backup(*b);
    setupUi(this);
    BackupName->setText(bc->getName());
    BackupSource->setText(bc->getSource());
    BackupCible->setText(bc->getTarget());
}

BackupItemWidget::~BackupItemWidget(){
    delete this;
}

Backup* BackupItemWidget::getBackup() const {
    return bc;
}

void BackupItemWidget::on_trashButton_clicked(){
     HomeWindow* parent = qobject_cast<HomeWindow*>(this->parent());

     //TODO
     Backup b(*bc);
//qDebug() <<b.getId();
//     parent->removeBackup(b);

     close();
//

}



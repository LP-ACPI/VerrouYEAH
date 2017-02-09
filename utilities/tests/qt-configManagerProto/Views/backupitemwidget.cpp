#include "backupitemwidget.h"
#include <QDebug>
#include <QDir>
#include <QDrag>
#include <QListWidgetItem>
#include <QMimeData>

BackupItemWidget::BackupItemWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    _parent = qobject_cast<HomeWindow*>(parent);
}

BackupItemWidget::BackupItemWidget(Backup *b,QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    _parent = qobject_cast<HomeWindow*>(parent);

    bc = new Backup(*b);
    BackupName->setText(bc->getName());
    BackupSource->setText(bc->getSource());
    BackupCible->setText(bc->getTarget());


   QPixmap saveIcon(":/images/save-icon.png");
   icon->setScaledContents(true);
   icon->setPixmap(saveIcon);

   QIcon delButIcon(QPixmap(":/images/trash-icon.png"));
   trashButton->setIconSize(QSize(30,50));
   trashButton->setIcon(delButIcon);

   QIcon decButIcon(QPixmap(":/images/Lock-Unlock-icon.png"));
   decryptButton->setIconSize(QSize(30,30));
   decryptButton->setIcon(decButIcon);

   setToolTip("<b>Nom : </b>" + bc->getName() + "<br/>" +
              "<b>Source : </b>" + bc->getSource() + "<br/>"+
              "<b>Cible : </b>" + bc->getTarget() + "<br/>"+
              "<b>Commentaire : </b>" + bc->getComent() + "<br/>"
   );

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
     _parent->removeBackup(*bc);
}


void BackupItemWidget::on_decryptButton_pressed(){
     _parent->decryptBackup(bc);
}

void BackupItemWidget::restartPos(){
    QPoint p;
    dragStartPosition = p;
}

void BackupItemWidget::mouseMoveEvent(QMouseEvent *event)
{
    int distance = (event->pos() - dragStartPosition).manhattanLength();
    if (!(event->buttons() & Qt::LeftButton))
          return;
      if (distance < QApplication::startDragDistance())
          return;

      QDrag *drag = new QDrag(this);
      QMimeData *mimeData = new QMimeData;
      mimeData->setData("text/uri-list",( "file:///" + (bc->getTarget()+ "/" + bc->getName() + ".vy")).toLatin1());
      drag->setMimeData(mimeData);

      QPixmap dragIcon(":/images/save-icon.png");
      drag->setPixmap(dragIcon.scaledToHeight( 50 ));

       Qt::DropAction dropAction = drag->exec( Qt::CopyAction );
       qDebug()<< drag->target()
               << dropAction
               << event->pos() .x();
}


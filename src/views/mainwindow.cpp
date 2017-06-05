#include "mainwindow.h"
#include "authdialog.h"
#include "../controllers/BackupController.h"

#include "progressdialog.h"

#include <QtGui>
#include <QMessageBox>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    UsersBackupController::getInstance().setCurrentUser();

    setupUi(this);

    std::string userName = UserController::getInstance().getCurrentUserLogin();
    setWindowTitle(QString::fromStdString("VerrouYEAH - " + userName));

    if(!QDir("decrypt").exists())
        actionDecryptDestination->setDisabled(true);

    newBackupButton->setAcceptDrops(true);
    initBackupList();

    connect(backupList, SIGNAL(itemClicked(QListWidgetItem*)),
            this ,SLOT(onBackupItemClicked(QListWidgetItem*)));


    trayIconMenu = new QMenu(this);

    QAction *quitAction = new QAction("Quitter", this);
    connect(quitAction,SIGNAL(triggered()),this,SLOT(aboutToclose()));
    trayIconMenu->addAction(quitAction);

    systemTrayIcon = new QSystemTrayIcon(QIcon(":/images/logo.png"),this);
    systemTrayIcon->setContextMenu(trayIconMenu);
    systemTrayIcon->show();
    systemTrayIcon->setToolTip("VerrouYeah");
    connect(&CompressCrypt::getInstance(),SIGNAL(cryptingStarted(QString)),this,SLOT(showEventTrayMessage(QString)));
    connect(&CompressCrypt::getInstance(),SIGNAL(error(QString)),this,SLOT(showTrayErrorMessage(QString)));
    connect(&Ftp::getInstance(),SIGNAL(error(QString)),this,SLOT(showTrayErrorMessage(QString)));
    connect(systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                    this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

MainWindow::~MainWindow(){
    if(detailBackupDialog)
        delete detailBackupDialog;
    if(backupForm)
        delete backupForm;
    if(userForm)
        delete userForm;
    if(recoverBackupDialog)
        delete recoverBackupDialog;
    if(trayIconMenu)
        delete trayIconMenu;
    if(systemTrayIcon)
        delete systemTrayIcon;
    close();

}

void MainWindow::initBackupList(){

    for(std::map<std::string,std::string> info
        : UsersBackupController::getInstance().getUsersBackupInfoList())
        addBackupItem(info);

}

void MainWindow::addBackupItem(std::map<std::string,std::string> backup_info){
    QListWidgetItem *item = new QListWidgetItem;
    BackupWidget *bcW = new BackupWidget(backup_info["key"],this);
    bcW->subscribeToBackup();
    bcW->setBackupInfo(backup_info);

    item->setSizeHint(QSize(1,80));
    backupList->addItem(item);
    backupList->setItemWidget(item,bcW);
    backupWidgetList.append(bcW);

    backupList->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(bcW,SIGNAL(removed(std::string)),this,SLOT(onBackupDeleted(std::string)));
}

void MainWindow::on_newBackupButton_clicked(){
    backupForm = new BackupForm(this);
    backupForm->show();
}

void MainWindow::on_actionUtilisateur_triggered(){
    userForm = new UserForm(this);
    userForm->show();
}

void MainWindow::on_actionDeconnexion_triggered(){
    if(!sureToExit())
        return;

    destroy();
    AuthDialog authDialog;
    authDialog.show();
    authDialog.exec();
}

void MainWindow::on_actionDecryptDestination_triggered(){
    QString path = QDir::toNativeSeparators("decrypt");
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void MainWindow::onBackupItemClicked(QListWidgetItem *backupItem){
     BackupWidget *bcW = qobject_cast<BackupWidget*>(backupList->itemWidget(backupItem));
     detailBackupDialog = new BackupDetailsDialog(bcW->getBackupKey(),bcW);
     detailBackupDialog->show();

     connect(detailBackupDialog,SIGNAL(removed(std::string)),this,SLOT(onBackupDeleted(std::string)));

}

void MainWindow::onBackupAdd(std::map<std::string, std::string> generatedBcInfo){
    addBackupItem(generatedBcInfo);
}

void MainWindow::onBackupDeleted(std::string backupKey){
    if(BackupController::getInstance().servicesAreBusy()){
        QMessageBox::warning(this, "Attention!",
                             "les services sont actuellement occupés à effectuer une sauvegarde. "
                             "\nMerci de reéssayer plus tard");
        return;
    }

    int row = 0;
    for(BackupWidget *bcW: backupWidgetList){
        if(bcW->getBackupKey() == backupKey){
            backupList->takeItem(row);
            backupWidgetList.removeAt(row);
            BackupController::getInstance().unsubscribeObserverFromBackup(bcW,backupKey);
        }
        ++row;
    }
        UsersBackupController::getInstance().deleteUsersBackup(backupKey);
}

void MainWindow::on_recoverBackupButton_clicked(){
    recoverBackupDialog = new RecoverBackupsDialog(this);
    recoverBackupDialog->show();
    connect(recoverBackupDialog,SIGNAL(addFoundData(std::map<std::string,std::string>)),
            this,SLOT(onBackupAdd(std::map<std::string,std::string>)));
    connect(recoverBackupDialog,SIGNAL(researchFinished(QString)),
            this,SLOT(showCustomTrayMessage(QString)));
}

void MainWindow::on_favoriteTargetsButton_clicked(){
   TargetChoiceDialog *targetChoice = new TargetChoiceDialog(this);
   targetChoice->show();
}


void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls()){
        event->acceptProposedAction();
    }
}

void MainWindow::showEventTrayMessage(QString backupName){

    systemTrayIcon->showMessage("VerrouYEAH",
                                backupName+" est en cours de sauvegarde. "
                                           "\nLes services risquent d'être occupés pendant un instant" );
}

void MainWindow::showCustomTrayMessage(QString message){
    systemTrayIcon->showMessage("VerrouYEAH",message);
}

void MainWindow::showTrayErrorMessage(QString errMessg){

    systemTrayIcon->showMessage("VerrouYEAH",
                              "Une erreur est survenue lors de l'éxécution de la sauvegarde :\n"+
                                errMessg,
                               QSystemTrayIcon::Warning );
}


void MainWindow::changeEvent(QEvent *event){
    if(event->type() == QEvent::WindowStateChange) {
        if(isMinimized())
            this->hide();
        event->ignore();
    }
}

void MainWindow::closeEvent(QCloseEvent *event){
   if(!sureToExit()){
        event->ignore();
    }
}

void MainWindow::aboutToclose(){
    close();
}



void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
 {
     switch (reason) {
     case QSystemTrayIcon::Trigger:
         if( isHidden()){
             this->show();
             if(isMinimized())
                 MainWindow::showMaximized();
         }else{
             this->hide();
         }
         break;
     case QSystemTrayIcon::DoubleClick:
         break;
     case QSystemTrayIcon::MiddleClick:
         break;

     default:
         ;
     }
 }
void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> droppedUrls = event->mimeData()->urls();
     int droppedUrlCnt = droppedUrls.size();
     for(int i = 0; i < droppedUrlCnt; i++) {
         QString localPath = droppedUrls[i].toLocalFile();
         QFileInfo fileInfo(localPath);
         if(fileInfo.isDir()) {
             backupForm = new BackupForm(this);
             backupForm->show();
             backupForm->setSourceText(fileInfo.absoluteFilePath());
             event->acceptProposedAction();
         }
     }
}

void MainWindow::on_actionAbout_triggered(){

    QMessageBox about(this);
    about.setWindowTitle("prototype VerrouYEAH!");

    about.setIconPixmap(QPixmap(":/images/logo.png"));

    about.setText("<h1>VerrouYEAH!</h1>"
                "Application de cryptage et planification de sauvegardes<br/>"
                "<br/>"
                  "Cette application a été développée dans le cadre du projet tuteuré des Licences professionnelles ACPI de L'IUT de Montpellier.<br/>"
                  "<br/>"
                  "Elle permet de planifier des sauvegardes automatiques à une fréquence et vers une destination choisies.<br/>"
                  "<br/>"
                  "A tout moment vous pouvez modifier ou supprimer la planification de vos sauvegardes.<br/>"
                  "<br/>"
                  "Vous avez la possibilité de récupérer vos sauvegardes enregistrées à une autre destination sous les identifiants qui leur sont associés <br/>"
                  "<br/>"
                  "Pour toute aide, des bulles informatives donnent les informations relatives aux fonctionnalités."
                  "<br/>"
);
    about.setInformativeText(
                "<i>"
                     "Développé par "
                           "<ul>"
                "<li>Faulon Maxime</li>"
                "<li>Necesany Marek</li>"
                "<li>Bourgeois Valentin</li> "
                "<li>Dalle-Cort Bérenger</li>"
                           "</ul>"
               "</i>"
    );
    about.setMaximumWidth(200);
    about.setStandardButtons(QMessageBox::Ok);
    about.show();
    about.exec();
}

bool MainWindow::sureToExit(){
    int response = QMessageBox::warning(this, "Attention!",
       "Vous allez quitter l'application. <br/>"
       "Vos sauvegardes ne seront plus synchronisées<br/>"
       "Etes-vous sûr?",
                 QMessageBox::Yes | QMessageBox::No);

    if(response == QMessageBox::No)
        return false;

    return true;
}

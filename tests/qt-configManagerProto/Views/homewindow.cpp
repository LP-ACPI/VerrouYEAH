#include "backupitemwidget.h"
#include "homewindow.h"
#include "authdialogwindow.h"
#include <QListWidgetItem>
#include <QMessageBox>
#include <QDebug>


HomeWindow::HomeWindow(QWidget *parent) :
    QMainWindow(parent),
    confMan(new ConfigManager)

{
    setupUi(this);
    setWindowTitle("Prototype VerrouYEAH!");
    setWindowIcon(QPixmap(":/images/LetsEncrypt_Logo.png"));

    if(confMan->noUser()){
        AuthDialogWindow *athWin = new AuthDialogWindow(confMan,this);
        athWin->show();
    } else {
        QMessageBox::information(this, "Bienvenue!",
                                 "Bienvenue  "+confMan->getUser()->getNom());
    }

    connect(backupList, SIGNAL(itemClicked(QListWidgetItem*)),
            this ,SLOT(onBackupItemClicked(QListWidgetItem*)));

    connect(confMan, SIGNAL(cryptInProgress(quint64,quint64)),
            this ,SLOT(cryptingProgress(quint64,quint64)));

    connect(this, SIGNAL(cryptingStart(Backup*)),
            this ,SLOT(onCryptingStart(Backup*)));

    connect(this, SIGNAL(cryptingDone()),
            this ,SLOT(onCryptingDone()));

    refresh();
}


HomeWindow::~HomeWindow() {
    delete confMan;
    this->close();
}

void HomeWindow::refresh(){
    backupList->clear();
    foreach(Backup bc, confMan->getUser()->getBackups()){
        QListWidgetItem *item = new QListWidgetItem;
        BackupItemWidget *bcW = new BackupItemWidget(&bc, this);

        item->setSizeHint(QSize(1,75));
        backupList->addItem(item);
        backupList->setItemWidget(item,bcW);
    }
}

void HomeWindow::addBackup(Backup &b){

    emit cryptingStart(&b);

    QListWidgetItem *item = new QListWidgetItem;
    BackupItemWidget *bcW = new BackupItemWidget(&b,this);

    item->setSizeHint(QSize(1,75));
    backupList->addItem(item);
    backupList->setItemWidget(item,bcW);
    bcW->setFocusPolicy(Qt::StrongFocus);

    confMan->addBackup(b);

    confMan->saveConfig();

}

void HomeWindow::modifBackup(Backup &oldBc,Backup &newBc){

    if(oldBc.getSource() != newBc.getSource()){
        removeBackup(oldBc);
        addBackup(newBc);
    } else {
        confMan->majBackup(newBc);
        refresh();

        // le CAST suivant produit un crash si utilisé par la suite. Du coup -> rafrachissement de la liste entière

        //    QListWidgetItem *item = backupList->currentItem();
        //     BackupItemWidget *bcW = qobject_cast<BackupItemWidget*>(backupList->itemWidget(item));

        //     bcW->setBackup(&b); --> crash


        //     bcW->setFocusPolicy(Qt::StrongFocus);
    }

    confMan->saveConfig();


}

void HomeWindow::removeBackup(Backup &b){
    confMan->delBackup(b);
    QListWidgetItem *item = backupList->currentItem();
    backupList->removeItemWidget(item);
    refresh();

    confMan->saveConfig();
}

ConfigManager* HomeWindow::getConfig() const{
    return confMan;
}

void HomeWindow::on_newBackupButton_clicked(){
    bcFormWin = new BackupFormWindow(this);
    bcFormWin->show();
}


void HomeWindow::onBackupItemClicked(QListWidgetItem *item){
    BackupItemWidget *bcW = qobject_cast<BackupItemWidget*>(backupList->itemWidget(item));
    Backup *bc = bcW->getBackup();
    bcFormWin = new BackupFormWindow(bc,this);
    bcFormWin->show();
}

void HomeWindow::onCryptingStart(Backup *bc){
    cryptProgress=new QProgressDialog(this);
    cryptProgress->setModal(true);
    cryptProgress->resize(500, cryptProgress->height());
    cryptProgress->show();

    const QString target = bc->getTarget()+ QLatin1Char('/')+bc->getName()+ QLatin1String(".vy");
    if(confMan->cryptDirectory( bc->getSource(), target )){
        emit cryptingDone();
    }
}

void HomeWindow::cryptingProgress(quint64 done, quint64 total){
    cryptProgress->setMaximum(total);
    cryptProgress->setWindowTitle("cryptage... "+ QString::number(done) + " / " +QString::number(total) + " fichiers cryptés");
    cryptProgress->setMinimum(0);
    cryptProgress->setValue(done);
}

void HomeWindow::onCryptingDone(){
    cryptProgress->close();
    delete cryptProgress;
}

void HomeWindow::on_actionRAZ_triggered(){
    confMan->resetConfig();

    int reponse = QMessageBox::question(this, "Remise à zéro",
                                        "Toutes les données viennent d'être supprimées. "
                                        "Souhaitez-vous quiter l'application ? "
                                        "(la création d'un nouvel utilisateur sera demandée)",
                                        QMessageBox ::Yes | QMessageBox::No
    );

    if (reponse == QMessageBox::No){
        AuthDialogWindow *athWin = new AuthDialogWindow(confMan,this);
        athWin->show();
        refresh();

    }   else if (reponse == QMessageBox::Yes)
        this->close();
}

void HomeWindow::on_actionUtilisateur_triggered(){
    AuthDialogWindow *athWin = new AuthDialogWindow(confMan,this);
    athWin->show();
}

void HomeWindow::on_action_propos_triggered()
{
    QMessageBox about;
    about.setWindowTitle("prototype VerrouYEAH!");

    about.setIconPixmap(QPixmap(":/images/logo_temporaire.png"));

    about.setText("<h1>VerrouYEAH!</h1>"
                "Prototype de cryptage de sauvegardes<br/>"
                "<br/>"
                    "Utilisation:<br/>"
                      "- cliquez sur \"nouvelle sauvegarde\" et entrez les paramètres de votre sauvegarde "
                      "pour crypter le dossier source vers dossier cible (sous la destination, elle portera le nom de <i>nom-sauvegarde</i>.vy)<br/>"
                      "- cliquez sur l'icône de suppression pour supprimer la sauvegarde et son dossier cible <br/>"
                      "- cliquez sur une sauvegarde pour voir ses paramètres et les modifer"
                     "<br/><br/>"
                    "options :<br/> "
                       "- RAZ : efface toutes les données (utilisateur et ses sauvegardes) du logiciel <br/>"
                       "- Utilisateur: modifier votre nom ou mot de passe <br/>"
                    "<br/><br/>"
);
    about.setInformativeText(
                "<i>"
                     "Développé par "
                           "<ul>"
                               "<li>Bourgeois Valentin</li> "
                               "<li>Dalle-Cort Bérenger</li>"
                               "<li>Faulon Maxime</li>"
                               "<li>Necesany Marek</li>"
                           "</ul>"
               "</i>"
    );

    about.setStandardButtons(QMessageBox::Ok);
    about.show();
    about.exec();
}

#include "progressdialog.h"
#include "../controllers/backupcontroller.h"
#include "../services/Scheduler.h"
#include <QMessageBox>
#include <QDesktopServices>


ProgressDialog::ProgressDialog(QWidget *parent) : QDialog(parent){

    setupUi(this);
    setModal(true);
    isFtp            = true;
    isUpload    = true;
    comprCryptServ = &CompressCrypt::getInstance();
    ftpServ = &Ftp::getInstance();
}

void ProgressDialog::setFtp(bool ftp){
    isFtp = ftp;
}

void ProgressDialog::setUpload(bool upload){
    isUpload = upload;
}

void ProgressDialog::init(){

    setUpConnections();

    topBar->setMinimum(0);
    topBar->setValue(0);
    midBar->setMinimum(0);
    midBar->setValue(0);
    bottomBar->setMinimum(0);
    bottomBar->setValue(0);

    if(!isFtp){
        bottomBar->hide();
        bottomLabel->hide();

        setMaximumHeight(200);
        setMinimumHeight(200);

        cancelButton->move(
                cancelButton->pos().x(),
                cancelButton->pos().y()-100
            );
    }
    setWindowTitle("Veuillez patienter durant l'exécution des processus");
}

void ProgressDialog::setUpConnections(){


    if(isFtp){
        if(isUpload)
            connect(ftpServ,SIGNAL(uploadStarted()),this,SLOT(onUploadBegan()));
        else
            connect(ftpServ,SIGNAL(downloadStarted()),this,SLOT(onDownloadBegan()));

        connect(ftpServ,SIGNAL(transferProgress(quint64,quint64)),this,SLOT(onTransferProgress(quint64,quint64)));
        connect(this,SIGNAL(canceled()),ftpServ,SLOT(cancelTranfer()));
        connect(ftpServ,SIGNAL(error(QString)),this,SLOT(onConnectivityErrorOccured(QString)));
    }

    connect(comprCryptServ,SIGNAL(compressStarted()), this,SLOT(onCompressBegan()));
    connect(comprCryptServ,SIGNAL(compressInProgress(quint64,quint64)),
                                    this,SLOT(onCompressProgress(quint64,quint64)));

    connect(comprCryptServ,SIGNAL(decompressStarted()), this,SLOT(onDecompressBegan()));

    connect(comprCryptServ,SIGNAL(cryptingStarted(QString)), this,SLOT(onCryptBegan(QString)));
    connect(comprCryptServ,SIGNAL(cryptInProgress(quint64,quint64)),
                                    this,SLOT(onCryptProgress(quint64,quint64)));

    connect(comprCryptServ,SIGNAL(decryptingStarted()), this,SLOT(onDecryptBegan()));
    connect(comprCryptServ,SIGNAL(decryptInProgress(quint64,quint64)),
                                     this,SLOT(onDecryptProgress(quint64,quint64)));
    connect(comprCryptServ,SIGNAL(error(QString)),this,SLOT(onCompressCryptErrorOccured(QString)));

}

void ProgressDialog::on_cancelButton_clicked(){
    emit canceled();
    close();
}

void ProgressDialog::onCryptBegan(QString){
    midBar->setDisabled(true);
    midLabel->setText("Compression en attente...");

    if(!isFtp){
        connect(comprCryptServ,SIGNAL(compressDone()),this,SLOT(onAllDone()));
    } else {
        bottomBar->setDisabled(true);
        bottomLabel->setText("Envoi sur serveur en attente...");
        connect(ftpServ,SIGNAL(finished()),this,SLOT(onAllDone()));
    }
}

void ProgressDialog::onCryptProgress(quint64 done,quint64 total){
    topLabel->setText(QString::number(done) + "  fichiers cryptés sur "+QString::number(total) );
    topBar->setMaximum(total);
    topBar->setValue(done);
}

void ProgressDialog::onCompressBegan(){
    midBar->setDisabled(false);
    topLabel->setText("Cryptage terminé");
}
void ProgressDialog::onCompressProgress(quint64 done,quint64 total){
    midLabel->setText(QString::number(done) + "  fichiers compressés sur "+QString::number(total) );
    midBar->setMaximum(total);
    midBar->setValue(done);
}

void ProgressDialog::onUploadBegan(){
    isUpload = true;
    bottomBar->setDisabled(false);
    midLabel->setText("Compression terminée" );
}

void ProgressDialog::onTransferProgress(quint64 done,quint64 total){
    if(isUpload){
        bottomBar->setMaximum(total);
        bottomBar->setValue(done);
        bottomLabel->setText(QString::number(done) + "  données téléversées sur "+QString::number(total) );
    }  else {
        topBar->setMaximum(total);
        topBar->setValue(done);
        topLabel->setText(QString::number(done) + "  données téléchargées sur "+QString::number(total) );
    }
}

void ProgressDialog::onDownloadBegan(){
    topLabel->setText("Téléchargement en cours...");
    midBar->setDisabled(true);
    bottomBar->setDisabled(true);
    midLabel->setText("Decompression en attente...");
    bottomLabel->setText("Décryptage en attente...");
}

void ProgressDialog::onDecompressBegan(){
    connect(comprCryptServ,SIGNAL(decryptingDone()),this,SLOT(onDecryptDone()));
    if(!isFtp){
        midBar->setDisabled(true);
        midLabel->setText("Décryptage en attente...");
        topLabel->setText("Décompression en cours");
        topBar->setMaximum(0);
        topBar->setMinimum(0);
    } else {
        midLabel->setText("Décompression en cours" );
        midBar->setDisabled(false);
        topLabel->setText("Téléchargement terminé");
        midBar->setMaximum(0);
        midBar->setValue(0);
    }
}

void ProgressDialog::onDecryptBegan(){
    if(!isFtp){
        topBar->setMaximum(100);
        topBar->setValue(100);
        midBar->setDisabled(false);
        topLabel->setText("Décompression terminée");
    } else {
        midBar->setMaximum(100);
        midBar->setValue(100);
        bottomBar->setDisabled(false);
        midLabel->setText("Décompression terminée");
    }
}

void ProgressDialog::onDecryptProgress(quint64 done,quint64 total){

    if(!isFtp){
        midLabel->setText(QString::number(done) + "  fichiers décryptés sur "+QString::number(total) );
        midBar->setMaximum(total);
        midBar->setValue(done);
    } else {
        bottomLabel->setText(QString::number(done) + "  fichiers décryptés sur "+QString::number(total) );
        bottomBar->setMaximum(total);
        bottomBar->setValue(done);
    }
}

void ProgressDialog::onDecryptDone(){
    QString path = QDir::toNativeSeparators("decrypt");
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
    onAllDone();
}

void ProgressDialog::onAllDone(){
    close();
}

void ProgressDialog::onConnectivityErrorOccured(QString){
    QMessageBox::warning(this, "Attention!",
                         "Une erreur de connection est survenue.\n "
                         "Etes-vous connectés à internet?\n"
                         "Merci de reéssayer plus tard");
    close();
    return;
}

void ProgressDialog::onCompressCryptErrorOccured(QString errMessage){
    QMessageBox::warning(this, "Attention!",
                         "Une erreur de (dé)cryptage/compression est survenue :\n "
                         + errMessage);
    close();
    return;
}

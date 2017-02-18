#include "progressdialog.h"
#include "../controllers/backupcontroller.h"


ProgressDialog::ProgressDialog(QWidget *parent) : QDialog(parent){

    setupUi(this);
    setModal(true);
    isFtp       = false;
    isUpload    = true;
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
        connect(&Ftp::getInstance(),SIGNAL(uploadStarted()),this,SLOT(onUploadBegan()));
        connect(&Ftp::getInstance(),SIGNAL(downloadStarted()),this,SLOT(onDownloadBegan()));
        connect(&Ftp::getInstance(),SIGNAL(transferProgress(quint64,quint64)),this,SLOT(onTransferProgress(quint64,quint64)));
        connect(this,SIGNAL(canceled()),&Ftp::getInstance(),SLOT(cancelTranfer()));
    }

    connect(&CompressCrypt::getInstance(),SIGNAL(compressStarted()), this,SLOT(onCompressBegan()));
    connect(&CompressCrypt::getInstance(),SIGNAL(compressInProgress(quint64,quint64)),
                                    this,SLOT(onCompressProgress(quint64,quint64)));

    connect(&CompressCrypt::getInstance(),SIGNAL(decompressStarted()), this,SLOT(onDecompressBegan()));

    connect(&CompressCrypt::getInstance(),SIGNAL(cryptingStarted()), this,SLOT(onCryptBegan()));
    connect(&CompressCrypt::getInstance(),SIGNAL(cryptInProgress(quint64,quint64)),
                                    this,SLOT(onCryptProgress(quint64,quint64)));

    connect(&CompressCrypt::getInstance(),SIGNAL(decryptingStarted()), this,SLOT(onDecryptBegan()));
    connect(&CompressCrypt::getInstance(),SIGNAL(decryptInProgress(quint64,quint64)),
                                     this,SLOT(onDecryptProgress(quint64,quint64)));
}

void ProgressDialog::on_cancelButton_clicked(){
    emit canceled();
    close();
}

void ProgressDialog::onCryptBegan(){
    midBar->setDisabled(true);
    midLabel->setText("Compression en attente...");

    if(!isFtp){
        connect(&CompressCrypt::getInstance(),SIGNAL(compressDone()),this,SLOT(onAllDone()));
    } else {
        bottomBar->setDisabled(true);
        bottomLabel->setText("Envoi sur serveur en attente...");
        connect(&Ftp::getInstance(),SIGNAL(finished()),this,SLOT(onAllDone()));
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
    QString upDownLoad = isUpload ? " téléversées " : " téléchargées ";
    if(isUpload){
        bottomBar->setMaximum(total);
        bottomBar->setValue(done);
    }  else {
        topBar->setMaximum(total);
        topBar->setValue(done);
    }
    topLabel->setText(QString::number(done) + "  données" + upDownLoad + "sur "+QString::number(total) );
}

void ProgressDialog::onDownloadBegan(){
    isUpload = false;
    midBar->setDisabled(true);
    bottomBar->setDisabled(true);
    midLabel->setText("Decompression en attente...");
    bottomLabel->setText("Décryptage en attente...");
}

void ProgressDialog::onDecompressBegan(){
    connect(&CompressCrypt::getInstance(),SIGNAL(decryptingDone()),this,SLOT(onAllDone()));
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
        mid->setMaximum(100);
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


void ProgressDialog::onAllDone(){
    close();
}

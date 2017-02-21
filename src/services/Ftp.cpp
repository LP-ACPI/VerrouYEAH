#include "Ftp.h"
#include <QtNetwork>
#include <QDebug>
#include <iostream>

/**
 * @brief Ftp::prepareFtp
 * @param host
 * @param username
 * @param pass
 * @param rewriteFile = true
 *
 * only public, simple, SSL free ftp(or http) servers
 */
void Ftp::prepareFtp(std::string host,
                     std::string username,
                     std::string pass,
                     int portNumber,
                     bool rewriteDownloadFile){

    networkAccessMan = new QNetworkAccessManager(this);

    this->host = QString::fromStdString(host);
    url->setHost(this->host);
    url->setUserName(QString::fromStdString(username));
    url->setPassword(QString::fromStdString(pass));
    url->setPort(portNumber);
    requestCanceled = false;

    rewriteDownloadedFile = rewriteDownloadFile;

    isBusy = true;
    connect(this,SIGNAL(error()),this,SLOT(cancelTranfer()));
}

/**
 * @brief Ftp::~Ftp
 */
Ftp::~Ftp() {
    delete networkAccessMan;
    delete url;
}

/**
 * @brief Ftp::ftpUpload
 * @param fileToUpload
 * @param destination
 * @return success|fail
 */
bool Ftp::ftpUpload(std::string fileToUpload, std::string destination){


    file = new QFile(QString::fromStdString(fileToUpload));
    QFileInfo fileInfo(QString::fromStdString(fileToUpload));

    QString fullUploadPath = host + "/"
            + QString::fromStdString(destination) + "/"
            + fileInfo.fileName();
qDebug() << fileInfo.fileName()
         << fileInfo.filePath()
         << fullUploadPath;

    url->setUrl( fullUploadPath );

    if (!file->open(QIODevice::ReadOnly)){
        std::cerr << fileInfo.fileName().toStdString() << ": lecture fichier impossible!" << std::endl;
        requestCanceled = true;
    }

    QByteArray data = file->readAll();
    if(data.count() <= 0){
        std::cerr << fileInfo.fileName().toStdString() << ": fichier inateignable!" << std::endl;
        requestCanceled = true;
    }

    networkReply = networkAccessMan->put((QNetworkRequest)*url, data);
    networkReply->setObjectName(fileInfo.fileName());

    connect(networkReply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(transferInProgress(qint64, qint64)));

    emit uploadStarted();
    std::cout << "téléversement de " << fileInfo.fileName().toStdString() << "..." << std::endl;
    return startTransfert(networkReply);
}

/**
 * @brief Ftp::ftpDownload
 * @param fileToDownload
 * @param destination
 * @return success|fail
 *
 */
bool Ftp::ftpDownload(std::string filePathToDownload, std::string destinationDir){

    url->setUrl(host+"/"+QString::fromStdString(filePathToDownload));

    networkReply = networkAccessMan->get((QNetworkRequest)*url);

    QFileInfo fileInfo(url->path());

    QDir dest(QString::fromStdString(destinationDir));
    if(!dest.exists())
        dest.mkpath(dest.absolutePath());
    QString fullNewFilePath = dest.absoluteFilePath(fileInfo.fileName());

    if (QFile::exists(fullNewFilePath)){
        std::cout << fileInfo.fileName().toStdString() << " existe déjà" << std::endl;
        requestCanceled = !rewriteDownloadedFile;
    }

    if(rewriteDownloadedFile){
        file = new QFile(fullNewFilePath);
        if(!file->open(QIODevice::WriteOnly)){//TODO throw? les abort de NetoworkReply s'en occuppent + signal error()
            std::cerr << fileInfo.fileName().toStdString() << ": écriture impossible" << std::endl;
            requestCanceled = true;
        }
    }

    networkReply->setObjectName(fileInfo.fileName());

    connect(networkReply, SIGNAL(readyRead()), this, SLOT(ftpReadyRead()));
    connect(networkReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(transferInProgress(qint64, qint64)));

    emit downloadStarted();
    std::cout << "téléchargement de " << fileInfo.fileName().toStdString() << "..." << std::endl;

    return startTransfert( networkReply) ||  !rewriteDownloadedFile;
}

/**
 * @brief Ftp::startTransfert
 * @param reply
 * @return
 */
bool Ftp::startTransfert(QNetworkReply *reply){

#ifndef QT_NO_SSL
   connect(reply, SIGNAL(sslErrors(QList<QSslError>)),this, SLOT(sslErrors(QList<QSslError>)));
#endif

    connect(reply, SIGNAL(finished()), this, SLOT(requestFinished()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(requestError(QNetworkReply::NetworkError)));

    if(requestCanceled)
        reply->abort();
    isBusy = false;
    return !requestCanceled;
}

/**
 * @brief Ftp::uploadInProgress
 * @param done
 * @param fileSize
 *
 * Slot de progression
 *
 */
void Ftp::transferInProgress(qint64 done, qint64 fileSize){

    if(requestCanceled)
        return;

    std::cout << "transfert :" << done <<"/" << fileSize << " octets"<< std::endl;
    emit transferProgress(done,fileSize);
}

/**
 * @brief Ftp::ftpReadyRead
 *
 * Slot called in download: read file
 */
void Ftp::ftpReadyRead()
{
    if(requestCanceled)
        return;

    if (file)
        file->write(networkReply->readAll());
}

/**
 * @brief Ftp::requestFinished
 */
void Ftp::requestFinished() {

    if(!networkReply->error())
           std::cout << networkReply->objectName().toStdString()
                << " transféré!"
            << std::endl;


    networkReply->deleteLater();
    if(!requestCanceled){
        networkReply = 0;
        if (file){
            file->flush();
            file->close();
            delete file;
            file = 0;
        }
    }

    isBusy = false;
    emit finished();
}

/**
 * @brief Ftp::requestError
 * @param err
 *
 */
void Ftp::requestError(QNetworkReply::NetworkError err) {
     qDebug() << "error : "<< err;
     emit error();

}

/**
 * @brief Ftp::sslErrors
 * @param sslErrors
 */
void Ftp::sslErrors(const QList<QSslError> &sslErrors)
{
#ifndef QT_NO_SSL
    foreach (const QSslError &error, sslErrors)
        fprintf(stderr, "SSL error: %s\n", qPrintable(error.errorString()));

#else
    Q_UNUSED(sslErrors);
#endif
    emit error();
}

void Ftp::cancelTranfer(){
    networkReply->abort();
    requestCanceled = true;
}

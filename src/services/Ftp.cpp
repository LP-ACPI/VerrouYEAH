#include "ftp.h"
#include <QtNetwork>
#include <QDebug>

//il me semble que ça change suivant si on est sous windows/unix
#define DIR_SEP "\\"

/**
 * @brief Ftp::Ftp
 * @param parent
 *
 * Constructor
 *
 */
Ftp::Ftp():
    networkAccessMan(new QNetworkAccessManager)
{}

Ftp::Ftp(std::string host,std::string username,std::string pass){
    prepareFtp(host,username,pass);
}

/**
 * @brief Ftp::~Ftp
 */
Ftp::~Ftp() {
    delete networkAccessMan;
    delete url;
    if (file)
        delete file;
}

void Ftp::prepareFtp(std::string host,std::string username,std::string pass){

    networkAccessMan = new QNetworkAccessManager(this);

    url = new QUrl;
    url->setHost(QString::fromStdString(host));
    url->setUserName(QString::fromStdString(username));
    url->setPassword(QString::fromStdString(pass));
}
/**
 * @brief Ftp::ftpUpload
 * @param fileToUpload
 * @param destination
 * @return success|fail
 *
 * c'est ici que se passe l'upload
 */
bool Ftp::ftpUpload(std::string fileToUpload, std::string destination) {

    file = new QFile(QString::fromStdString(fileToUpload));
    QFileInfo fileInfo(QString::fromStdString(fileToUpload));
    url->setUrl(QString::fromStdString(destination));

    if (!file->open(QIODevice::ReadOnly))
        return false;

    QByteArray data = file->readAll();
    QNetworkReply *reply = networkAccessMan->put((QNetworkRequest)*url, data);
    reply->setObjectName(fileInfo.fileName());

    connect(reply, SIGNAL(finished()), this, SLOT(requestFinished()));
    connect(reply, SIGNAL(uploadProgress(qint64, qint64)),this, SLOT(uploadInProgress(qint64, qint64)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this, SLOT(requestError(QNetworkReply::NetworkError)));

    return true;

}

/**
 * @brief Ftp::ftpDownload
 * @param fileToDownload
 * @param destination
 * @return success|fail
 *
 * download
 */
bool Ftp::ftpDownload(std::string filePathToDownload, std::string destinationFilepath)
{
    url->setUrl(QString::fromStdString(filePathToDownload));
    QNetworkReply *reply = networkAccessMan->get((QNetworkRequest)*url);

    QFileInfo fileInfo(url->path());

    file = new QFile(QString::fromStdString(destinationFilepath));

    if(!file->open(QIODevice::WriteOnly))
        return false;

    reply->setObjectName(fileInfo.fileName());


    connect(reply, SIGNAL(readyRead()), this, SLOT(ftpReadyRead()));
    connect(reply, SIGNAL(finished()), this, SLOT(requestFinished()));

    connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(downloadInProgress(qint64, qint64)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(requestError(QNetworkReply::NetworkError)));

    return true;
}

/**
 * @brief Ftp::uploadInProgress
 * @param done
 * @param fileSize
 *
 * Slot déclenché+mis à jour durant la progression de l'upload
 *
 */
void Ftp::uploadInProgress(qint64 done, qint64 fileSize) {
    QNetworkReply *reply = (QNetworkReply*)sender();
    qDebug() << "uploading..."<<"{\"ref\":\""
            <<reply->objectName()
           <<"\" , \"done\":\""
          <<done
         <<"\", \"total\":\""
        <<fileSize
       <<"\"}";
    emit transferInProgress(done,fileSize);
}

/**
 * @brief Ftp::ftpReadyRead
 *
 * Slot appelé durant download: récupérer dans un fichier ce qu'on reçoit par réseau
 */
void Ftp::ftpReadyRead()
{
    QNetworkReply *reply = (QNetworkReply*)sender();
    if (file)
        file->write(reply->readAll());
}

/**
 * @brief Ftp::downloadInProgress
 * @param done
 * @param fileSize
 *
 * Slot déclenché+mis à jour durant téléchargement (avec en données: taille théoriques de fichiers - taille reçue vs taille totale)
 */
void Ftp::downloadInProgress(qint64 done, qint64 fileSize) {
    QNetworkReply *reply = (QNetworkReply*)sender();
    qDebug() << "download..."<<"{\"ref\":\""
            <<reply->objectName()
           <<"\" , \"done\":\""
          <<done
         <<"\", \"total\":\""
        <<fileSize
       <<"\"}";
    emit transferInProgress(done,fileSize);
}


/**
 * @brief Ftp::requestFinished
 *
 * slot déclenché en fin de téléchargement/versement
 *
 */
void Ftp::requestFinished() {
    QNetworkReply *reply = (QNetworkReply*)sender();
    if(!reply->error()){
        qDebug() << "Fini"<<"{\"ref\":\""
                <<reply->objectName()
               <<" done!"
              <<"\"}";
    } else qDebug() << reply->errorString();

    file->flush();
    file->close();
    reply->deleteLater();
    delete file;
    reply = 0;
    file = 0;
    networkAccessMan = 0;
}

/**
 * @brief Ftp::requestError
 * @param err
 *
 * slot déclenché par une erreur
 */
void Ftp::requestError(QNetworkReply::NetworkError err) {
     qDebug() << "error : "<< err;
     emit finished();
}

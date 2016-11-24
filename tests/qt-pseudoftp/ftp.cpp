#include "ftp.h"
#include <QtWidgets>
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
Ftp::Ftp(QWidget* parent):
    QDialog(parent)
{
    setupUi(this);

    nam = new QNetworkAccessManager();

    logo->setPixmap(QPixmap(":/logo_temporaire.png").scaled(115,85));

    downloadChoice->setChecked(true);
    transferButton->setText(tr("Télécharger"));

    hostInput->setToolTip("Addresse du serveur ftp");
    userInput->setToolTip("identifiant");
    pwdInput->setToolTip("mot de passe");
    serverInput->setToolTip("Chemin 'absolu' vers fichier/dossier");
    connect( file_dirChoice, SIGNAL(clicked()), this, SLOT(openDialog()));

}

/**
 * @brief Ftp::~Ftp
 */
Ftp::~Ftp() {
    delete nam;
    delete url;
    if (file)
        delete file;
    delete this;
}


/**
 * @brief Ftp::openDialog
 *
 * dialogue de choix de fichier source à uploader / dossier cible où sauvegarder le fichier téléchargé
 * on conserve le lien vers fichier local dans le texte du bouton
 */
void Ftp::openDialog(){

    if(uploadChoice->isChecked()){
        QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString());
        file_dirChoice->setText(fichier);
    }else if(downloadChoice->isChecked()){
        QString dossier = QFileDialog::getExistingDirectory(this);
        file_dirChoice->setText(dossier);
    }
}
/**
 * @brief Ftp::on_quitButton_clicked
 *
 * Slot déclenché par clic sur quitter: ouverture du dialogue d'adieu
 */
void Ftp::on_quitButton_clicked()
{
    QMessageBox bye;
    bye.setWindowTitle("VerrouYEAH - bye");
    bye.setText("<h1>VerrouYEAH!</h1>"
                "- exemple d'échange de fichiers individuels avec un serveur ftp (ou autre) -<br/>"
                "et de manipulation d'interface Qt.<br/><br/>");
    bye.setInformativeText("<i>"
                           "Développé par "
                           "<ul>"
                           "<li>V. Bourgeois</li> "
                           "<li>B. Dalle-Cort</li>"
                           "<li>M. Faulon</li>"
                           "<li>M. Necesany</li>"
                           "</ul>"
                           "</i>"
    );

    bye.setIconPixmap(QPixmap(":/logo_temporaire.png"));
    bye.setStandardButtons(QMessageBox::Ok);
    bye.setDefaultButton(QMessageBox::Ok);
    bye.show();
    bye.exec();

    this->close();
}

/**
 * @brief Ftp::on_returnPressed
 *
 * Slot déclenché au signal: appui sur entrée
 */
void Ftp::on_returnPressed()
{
    on_transferButton_clicked();
}

/**
 * @brief Ftp::on_downloadChoice_clicked
 *
 * Slot déclenché au signal: clic sur bouon radio "Télécharger -> on désactive l'autre choix + changement de texte
 */
void Ftp::on_downloadChoice_clicked()
{
    uploadChoice->setChecked(false);
    serverLabel->setText(tr("Fichier à télécharger:"));
    clientLabel->setText(tr("Dossier de destination:"));
    downloadChoice->setChecked(true);
    transferButton->setText(tr("Télécharger"));
}
/**
 * @brief Ftp::on_uploadChoice_clicked
 *
 * de même mais pour l'upload
 */
void Ftp::on_uploadChoice_clicked()
{
    downloadChoice->setChecked(false);
    serverLabel->setText(tr("Dossier de destination:"));
    clientLabel->setText(tr("Fichier à téléverser:"));
    uploadChoice->setChecked(true);
    transferButton->setText(tr("Téléverser"));
}

/**
 * @brief Ftp::on_transferButton_clicked
 *
 * Gestion de l'appui sur boutton de déclenchement du téléchargement/versement
 *
 * -> vérification si tous les champs sont remplis (certains sites ne nécéssitent pas l'utilisateur & mot de passe)
 * -> il s'agit d'un dialogue simpliste, gérant un unique fichier, qui si à télécharger n'a de conu que son nom apparemment
 *
 */
void Ftp::on_transferButton_clicked(){


    if(     //userInput->text().isEmpty()
            //|| pwdInput->text().isEmpty()
             hostInput->text().isEmpty()
            || serverInput->text().isEmpty()
            || file_dirChoice->text().isEmpty()){

        if(QMessageBox::information(this, "Attention!",
                                    "Merci de remplir toutes les informations!",NULL))
            return;
    }

    nam = new QNetworkAccessManager(this);

    host = protoChoice->currentText() + hostInput->text();
    url = new QUrl;
    url->setHost(host);
    url->setUserName(userInput->text());
    url->setPassword(pwdInput->text());

    if(protoChoice->currentText()=="ftp://") url->setPort(22);


    progressDialog = new QProgressDialog(this);
    if(uploadChoice->isChecked()){

        progressDialog->setWindowTitle("Téléversement");
        ftpUpload(file_dirChoice->text(),serverInput->text());
    }else if(downloadChoice->isChecked()){

        progressDialog->setWindowTitle("Téléchargement");
        ftpDownload(serverInput->text(),file_dirChoice->text());
    }
}
/**
 * @brief Ftp::ftpUpload
 * @param fileToUpload
 * @param dest
 * @return success|fail
 *
 * c'est ici qu se passe l'upload
 */
bool Ftp::ftpUpload(QString fileToUpload, QString dest) {

    file = new QFile(fileToUpload);
    QFileInfo fileInfo(fileToUpload);
    url->setUrl(host+dest+"/"+fileInfo.fileName());

    if (!file->open(QIODevice::ReadOnly))
        return false;

    QByteArray data = file->readAll();
    QNetworkReply *reply = nam->put((QNetworkRequest)*url, data);
    reply->setObjectName(fileInfo.fileName());

    connect(reply, SIGNAL(finished()), this, SLOT(requestFinished()));
    connect(reply, SIGNAL(uploadProgress(qint64, qint64)),this, SLOT(uploadInProgress(qint64, qint64)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this, SLOT(requestError(QNetworkReply::NetworkError)));

    return true;

}

/**
 * @brief Ftp::ftpDownload
 * @param fileToDownload
 * @param dest
 * @return success|fail
 *
 * download
 */
bool Ftp::ftpDownload(QString fileToDownload, QString dest)
{
    url->setUrl(host+fileToDownload);
    QNetworkReply *reply = nam->get((QNetworkRequest)*url);

    QFileInfo fileInfo(url->path());

    file = new QFile(dest+DIR_SEP+fileInfo.fileName());

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
    progressDialog->show();
    progressDialog->setWindowTitle("upload: "+ QString::number(done) + "by / " +QString::number(fileSize)+ "by");
    progressDialog->setMaximum(fileSize);
    progressDialog->setValue(done);
}

/**
 * @brief Ftp::ftpReadyRead
 *
 * Slot appelé durant download: récupérer dans un fichier ce qu'on reçoit par réseau
 */
void Ftp::ftpReadyRead()
{
    QNetworkReply *reply = (QNetworkReply*)sender();

    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
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

    progressDialog->show();

    progressDialog->setWindowTitle("download: "+ QString::number(done) + "by ");
    progressDialog->setMaximum(fileSize);
    progressDialog->setValue(done);
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
    progressDialog->hide();

    file->flush();
    file->close();
    reply->deleteLater();  //important!!!!
    delete file;
    reply = 0;
    file = 0;
    nam = 0;
}

/**
 * @brief Ftp::requestError
 * @param err
 *
 * slot décleché par une erreur
 */
void Ftp::requestError(QNetworkReply::NetworkError err) {
     qDebug() << "error : "<< err;
     QMessageBox::critical(this, "Erreur", tr("Erreur de transfert: %1.").arg(err));
     emit finished();
}

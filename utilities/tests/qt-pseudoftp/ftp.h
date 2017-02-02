#ifndef Ftp_H
#define Ftp_H

#include "ui_Dialog.h"
#include <QtWidgets>
#include <QtNetwork>

/**
 * Petit pseudo-gestionnaire Ftp qui permet juste de télécharger un fichier depuis un serveur ftp
 * (non sftp(apparemment non reconnu par QUrl) - par exemple ne marche pas avec le serveur de l'IUT)
 * ou de téleverser un fichier local vers ce serveur
 * Mais paraît qu'on peut se servir de QTcpSocket pour envoyer des commandes ftp brutes
 *
 */


//le second héritage évite d'utiliser le pointeur vers ui l'interface Dialog.ui
// du style 'ui->QWidget->text()', il permet de de raccourcir en QWidget->text()
class Ftp: public QDialog, private Ui::Dialog {
    Q_OBJECT
private:
    QNetworkAccessManager* nam;
    QNetworkReply* reply;
    QString host;
    QUrl* url;
    QFile* file;

    QProgressDialog *progressDialog;
    QDialog *errorDialog;


public:
    explicit Ftp(QWidget *parent = 0);
    ~Ftp();

    bool ftpUpload(QString,QString);
    bool ftpDownload(QString,QString);

signals:
    void finished();
    void error(QNetworkReply::NetworkError);

protected slots:
    //certains slots n'ont pas besoin de spécification pour établir la connexion à un signal:
    //la connexion se fait par la syntaxe 'on_widgetConcerné_signal()'
    void on_transferButton_clicked();
    void on_returnPressed();
    void on_uploadChoice_clicked();
    void on_downloadChoice_clicked();
    void on_quitButton_clicked();

//mais ceux là si
    void openDialog();
    void ftpReadyRead();
    void uploadInProgress(qint64, qint64);
    void downloadInProgress(qint64, qint64);
    void requestFinished();
    void requestError(QNetworkReply::NetworkError);
};

#endif /// Ftp_H

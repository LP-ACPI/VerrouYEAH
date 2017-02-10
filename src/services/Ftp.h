#ifndef Ftp_H
#define Ftp_H

#include <QUrl>
#include <QFile>
#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>


class Ftp : public QObject {
    Q_OBJECT
private:
    QNetworkAccessManager *networkAccessMan;
    QNetworkReply *networkReply;
    QString host;
    QUrl* url;
    QFile *file;
    bool requestCanceled;
    bool rewriteDownloadedFile;

    bool startTransfert(QNetworkReply*);
public:
    Ftp(QObject *parent=0): QObject(parent)
    {   url = new QUrl; }
    Ftp(std::string host,
        std::string username,
        std::string pass,
        int portNumber = 21,
        bool rewriteFile = true,
        QObject *parent=0): QObject(parent)
    {   prepareFtp(host,username,pass,portNumber,rewriteFile); }

    ~Ftp();

    void prepareFtp(std::string,
                    std::string,
                    std::string,
                    int portNumber,
                    bool rewriteDownloadFile);
    bool ftpUpload(std::string,std::string);
    bool ftpDownload(std::string,std::string);

    void setDownloadRewrite(bool rewriteFile)
    {    rewriteDownloadedFile = rewriteFile;   }

signals:
    void started();
    void finished();
    void error();
    void transferProgress(quint64,quint64);

private slots:
    void ftpReadyRead();
    void transferInProgress(qint64, qint64);
    void requestFinished();
    void requestError(QNetworkReply::NetworkError);
    void sslErrors(const QList<QSslError>&);
};


#endif /// Ftp_H

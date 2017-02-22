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
    bool rewriteDownloadedFile;
    bool requestCanceled = false;
    bool isBusy = false;


    bool startTransfert(QNetworkReply*);

    explicit Ftp(QObject *parent=0): QObject(parent)
    {   url = new QUrl; }


public:
    static Ftp &getInstance(){
        static Ftp instance;
        return instance;
    }

    ~Ftp();

    void prepareFtp(std::string,
                    std::string,
                    std::string,
                    int portNumber = 21,
                    bool rewriteDownloadFile = true);
    bool ftpUpload(std::string,std::string);
    bool ftpDownload(std::string,std::string);

    void setDownloadRewrite(bool rewriteFile)
    {    rewriteDownloadedFile = rewriteFile;   }


    bool isCurrentlyBusy(){
        return isBusy;
    }
    bool connectionErrorOccured(){
        return requestCanceled;
    }

signals:
    void downloadStarted();
    void uploadStarted();
    void finished();
    void error();
    void transferProgress(quint64,quint64);

private slots:
    void ftpReadyRead();
    void transferInProgress(qint64, qint64);
    void requestFinished();
    void requestError(QNetworkReply::NetworkError);
    void sslErrors(const QList<QSslError>&);
    void cancelTranfer();
};


#endif /// Ftp_H

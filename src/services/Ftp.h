#ifndef Ftp_H
#define Ftp_H

#include <QtWidgets>
#include <QtNetwork>


class Ftp : public QObject {
    Q_OBJECT
private:
    QNetworkAccessManager* networkAccessMan;
    QNetworkReply* networkReply;
    QString host;
    QUrl* url;
    QFile *file;

public:
    Ftp(const Ftp&);
    Ftp(std::string,std::string,std::string);
    Ftp();
    ~Ftp();

    bool ftpUpload(std::string,std::string);
    bool ftpDownload(std::string,std::string);

    void prepareFtp(std::string,std::string,std::string);

signals:
    void finished();
    void error(QNetworkReply::NetworkError);
    void transferInProgress(quint64,quint64);

protected slots:

    void ftpReadyRead();
    void uploadInProgress(qint64, qint64);
    void downloadInProgress(qint64, qint64);
    void requestFinished();
    void requestError(QNetworkReply::NetworkError);
};

#endif /// Ftp_H

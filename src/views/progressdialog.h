#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include "ui_progressdialog.h"
#include "../services/CompressCrypt.h"
#include "../services/Ftp.h"
#include <QDialog>

class ProgressDialog : public QDialog, private Ui::ProgressDialog
{
    Q_OBJECT
    bool isFtp;
    bool isUpload;

    Ftp *ftpServ;

    void setUpConnections();
public:
    explicit ProgressDialog(QWidget *parent = 0);

    void setFtp(bool);
    void setUpload(bool);
    void init();

signals:
    void canceled();

public slots:
    void on_cancelButton_clicked();

    void onAllDone();

    void onCryptBegan();
    void onDecryptBegan();
    void onDecryptDone();

    void onUploadBegan();
    void onDownloadBegan();

    void onCompressBegan();
    void onDecompressBegan();

    void onCryptProgress(quint64,quint64);
    void onDecryptProgress(quint64,quint64);
    void onCompressProgress(quint64,quint64);
    void onTransferProgress(quint64,quint64);
};

#endif // PROGRESSDIALOG_H

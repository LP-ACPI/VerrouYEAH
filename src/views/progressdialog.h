#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QWidget>

class ProgressDialog : public QWidget
{
    Q_OBJECT
public:
    explicit ProgressDialog(QWidget *parent = 0);

signals:
    void finisheed();
    void aborted();

public slots:
    void onCryptProgress(quint64,quint64);
    void onDecryptProgress(quint64,quint64);
    void onCompressProgress(quint64,quint64);
    void onUploadProgress(quint64,quint64);
    void onDownloadProgress(quint64,quint64);
};

#endif // PROGRESSDIALOG_H

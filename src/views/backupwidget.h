#ifndef BACKUPWIDGET_H
#define BACKUPWIDGET_H

#include "ui_backupwidget.h"
#include "../services/Observer.h"
#include "json.hpp"
#include <QWidget>
#include <QListWidgetItem>

class BackupWidget : public QWidget, private Ui::BackupWidget, public Observer
{
    Q_OBJECT
    std::string backupKey;
    std::map<std::string,std::string> targetInfo;

    QWidget *_parent;

    virtual void update(nlohmann::json)  override;

public:
    explicit BackupWidget(QWidget *parent = 0);

    void setBackupInfo(std::map<std::string,std::string>);

    std::string getBackupKey()
    { return backupKey; }


signals:
    void removed(std::string);
    void updated(std::string);

public slots:
    void on_configButton_clicked();
    void on_trashButton_clicked();
    void on_decryptButton_clicked();

    void onBackupUpdated(std::map<std::string,std::string>);

};

#endif // BACKUPWIDGET_H

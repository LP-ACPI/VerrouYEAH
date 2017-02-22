#ifndef DETAILSSAUVEGARDE_H
#define DETAILSSAUVEGARDE_H

#include "ui_backupdetailsdialog.h"
#include "../services/Observer.h"
#include <QDialog>
#include <QFileSystemModel>
#include "backupwidget.h"

class BackupDetailsDialog : public  QDialog, private Ui::BackupDetailsDialog, public Observer
{
    Q_OBJECT

    QWidget _parent;
    QFileSystemModel *model ;
    std::string backupKey;
    std::string targetTag;

    virtual void update(nlohmann::json)  override;

public:
    explicit BackupDetailsDialog(std::string, QWidget *parent = 0);
    ~BackupDetailsDialog();

signals:
    void removed(std::string);
public slots:
    void on_configButton_clicked();
    void on_trashButton_clicked();
    void on_decryptButton_clicked();
    void on_backButton_clicked();
    void onBackupUpdated(std::map<std::string,std::string>);

private:
    void updateBackupInfo(std::string);

};

#endif // DETAILSSAUVEGARDE_H

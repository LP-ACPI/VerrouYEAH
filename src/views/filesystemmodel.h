#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H
#include <QFileSystemModel>

class FileSystemModel: public QFileSystemModel
{
    Q_OBJECT
public:
    explicit FileSystemModel(QObject *parent = 0);
    QVariant data ( const QModelIndex &, int ) const override;
};

#endif // FILESYSTEMMODEL_H

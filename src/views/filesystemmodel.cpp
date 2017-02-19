#include "filesystemmodel.h"
#include <QFileIconProvider>
#include <QFileInfo>

FileSystemModel::FileSystemModel(QObject *parent):QFileSystemModel(parent){}

QVariant FileSystemModel::data ( const QModelIndex & index, int role ) const {

    if (!index.isValid())
        return QVariant();

    if( index.column() == 0 && role == Qt::DecorationRole ){
        auto path = index.data(QFileSystemModel::FilePathRole).toString();
        QFileInfo infoItem(path);
        if(infoItem.isFile())
            return QFileIconProvider().icon(QFileIconProvider::File).pixmap(15,15);
        else if(infoItem.isDir())
              return QFileIconProvider().icon(QFileIconProvider::Folder).pixmap(15,15);
    }
    return QFileSystemModel::data(index, role);
}

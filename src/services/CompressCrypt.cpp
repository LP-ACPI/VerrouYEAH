#include "CompressCrypt.h"
#include <iostream>

CompressCrypt::CompressCrypt(QObject *parent) :
    QObject(parent)
{}

bool CompressCrypt::compressDir(const QString &sourceFolder, const QString &destinationFile)
{
    QDir src(sourceFolder);
    if(!src.exists())
        return false;

    file.setFileName(destinationFile);
    if(!file.open(QIODevice::WriteOnly))
        return false;

    dataStream.setDevice(&file);

    emit compressStarted();

    totalFileCount = countFiles(sourceFolder,0);

    bool success = compress(sourceFolder, "",0) > 0;
    file.close();

    emit compressDone();

    return success;
}

quint64 CompressCrypt::compress(const QString &sourceFolder,const QString &prefex, quint64 count){

    QDir dir(sourceFolder);
    if(!dir.exists())
        return 0;

    dir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden);
    QFileInfoList foldersList = dir.entryInfoList();

    for(int i=0; i<foldersList.length(); i++)
    {
        QString folderName = foldersList.at(i).fileName();
        QString folderPath = dir.absolutePath()+QDir::separator()+folderName;
        QString newPrefex = prefex+QDir::separator()+folderName;

        count = compress(folderPath, newPrefex,count);
    }

    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Hidden);
    QFileInfoList filesList = dir.entryInfoList();

    for(int i=0; i<filesList.length(); i++)
    {

        QFile file(filesList.at(i).filePath());

        if(!file.open(QIODevice::ReadOnly))
            return 0;

        dataStream << QString(prefex+QDir::separator()+filesList.at(i).fileName());
        dataStream << qCompress(file.readAll());

        file.close();
        count++;
        emit compressInProgress(count,totalFileCount);
    }
    return true;
}

bool CompressCrypt::decompressDir(const QString &sourceFile,const QString &destinationFolder) {

    QFile src(sourceFile);
    if(!src.exists())
        return false;

    QDir dir;
    if(!dir.mkpath(destinationFolder))
        return false;

    file.setFileName(sourceFile);
    if(!file.open(QIODevice::ReadOnly))
        return false;

    dataStream.setDevice(&file);

    emit decompressStarted();

    while(!dataStream.atEnd())
    {
        QString fileName;
        QByteArray data;

        dataStream >> fileName >> data;

        QString subfolder;
        for(int i=fileName.length()-1; i>0; i--)
        {
            if((QString(fileName.at(i)) == QString("\\")) || (QString(fileName.at(i)) == QString("/")))
            {
                subfolder = fileName.left(i);
                dir.mkpath(destinationFolder+subfolder);
                break;
            }
        }

        QFile outFile(destinationFolder+fileName);
        if(!outFile.open(QIODevice::WriteOnly)){

            file.close();
            return false;
        }
        outFile.write(qUncompress(data));
        outFile.close();
    }

    file.close();

    emit decompressDone();

    return true;
}

bool CompressCrypt::cryptDir(const QString &source,const QString &cible, char *key){

    QDir sourceDir(source);
    if(!sourceDir.exists())
        return false;

    emit cryptingStarted();

    totalFileCount = countFiles(source,0);
    bool success = cryptDirWithCount(source,cible,0,key) > 0;

    emit cryptingDone();

    return success;
}

quint64 CompressCrypt::cryptDirWithCount(const QString &source,const QString &cible, quint64 crypted ,char *key){

    QFileInfo srcFileInfo(source);
    if (srcFileInfo.isDir()) {

        QDir targetDir;
        if (!targetDir.mkpath(cible))
            return -1;

        QDir sourceDir(source);
        sourceDir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden);
        QStringList sub_dirs = sourceDir.entryList();

        foreach (const QString &sub_dir_name, sub_dirs) {
            const QString subSource  = source + QDir::separator() + sub_dir_name;
            const QString subCible = cible +  QDir::separator()  + sub_dir_name;
            crypted = cryptDirWithCount(subSource, subCible,crypted,key);
        }
    } else {
        cryptMan.cryptFile(source.toStdString(), cible.toStdString(), key);
        crypted++;
    }
    emit cryptInProgress(crypted,totalFileCount);
    return crypted;

}

bool CompressCrypt::decryptDir(const QString &source,const QString &cible, char* key){

    QDir sourceDir(source);
    if(!sourceDir.exists())
        return false;

    emit decryptingStarted();
    totalFileCount = countFiles(source,0);

    bool success = decryptDirWithCount(source,cible,0, key) > 0;
    emit decryptingDone();

    return success;
}

quint64 CompressCrypt::decryptDirWithCount(const QString &source,const QString &cible,quint64 decrypted,char* key){

    QFileInfo srcFileInfo(source);
    if (srcFileInfo.isDir()) {

        QDir targetDir;
        if (!targetDir.mkpath(cible))
            return -1;

        QDir sourceDir(source);
        sourceDir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden);
        QStringList sub_dirs = sourceDir.entryList();

        foreach (const QString &sub_dir_name, sub_dirs) {
            const QString subSource  = source + QDir::separator() + sub_dir_name;
            const QString subCible = cible + QDir::separator() + sub_dir_name;

            decrypted = decryptDirWithCount(subSource, subCible, decrypted, key);
        }
    } else {
        cryptMan.decryptFile(source.toStdString(), cible.toStdString(), key);
        decrypted++;
    }
    emit decryptInProgress(decrypted,totalFileCount);
    return decrypted;
}

quint64 CompressCrypt::countFiles(const QString &source, quint64 ctn){
    QFileInfo srcInfo(source);
    if (srcInfo.isDir()) {
        QDir srcDir(source);
        srcDir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden);
        QStringList elements = srcDir.entryList();

        foreach (const QString &el, elements) {
            const QString subEl  = source + QDir::separator() + el;
            QFileInfo srcInfo(subEl);
             if (srcInfo.isDir())
                 ctn+=countFiles(subEl);
             else
                 ctn++;
        }
    }
    return ctn;
}

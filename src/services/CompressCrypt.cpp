#include "CompressCrypt.h"
#include <iostream>
#include <QUrl>
#include <QCoreApplication>

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

    emit(compressStarted());

    isBusy = true;
    totalDataCount = countFiles(sourceFolder,0);

    bool success = compress(sourceFolder, "",0) > 0;
    file.close();

    emit(compressDone());

    isBusy = false;
    return success;
}

quint64 CompressCrypt::compress(const QString &source,const QString &prefex, quint64 count){

    QDir dir(source);
    if(dir.exists()){

        dir.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs | QDir::Hidden);
        QFileInfoList subElemsList = dir.entryInfoList();

        for(int i=0; i<subElemsList.length(); i++)
        {
            QString sourceName = subElemsList.at(i).fileName();
            QString sourcePath = subElemsList.at(i).filePath();
            QString newPrefex = prefex+"/"+sourceName;

            count = compress(sourcePath, newPrefex,count);
            QCoreApplication::processEvents();
        }

    } else {

        QFile file(source);
        if(!file.open(QIODevice::ReadOnly))
            return 0;

        dataStream << prefex;
        dataStream << qCompress(file.readAll());

        file.close();

        count++;
    }
    emit(compressInProgress(count,totalDataCount));
    return count;
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

    emit(decompressStarted());

    isBusy = true;
    while(!dataStream.atEnd())
    {
        QString fileName;
        QByteArray data;

        dataStream >> fileName >> data;
        data.size();

        QString subfolder;
        for(int i=fileName.length()-1; i>0; i--)
        {
            if(QString(fileName.at(i)) ==QString("/") || QString(fileName.at(i)) ==QString("\\"))
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
        QCoreApplication::processEvents();
    }

    file.close();

    emit(decompressDone());

    isBusy = false;
    return true;
}

bool CompressCrypt::cryptDir(const QString &source,const QString &cible, char *key){

    QDir sourceDir(source);
    if(!sourceDir.exists())
        return false;

    emit(cryptingStarted());
    isBusy = true;
    totalDataCount = countFiles(source,0);
    bool success = cryptDirWithCount(source,cible,0,key) > 0;

    emit cryptingDone();
    isBusy = false;
    return success;
}

quint64 CompressCrypt::cryptDirWithCount(const QString &source,const QString &cible, quint64 crypted , char *key){

    QDir sourceDir(source);
    if (sourceDir.exists()) {

        QDir targetDir;
        if (!targetDir.mkpath(cible))
            return -1;

        sourceDir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden);
        QStringList sub_dirs = sourceDir.entryList();

        foreach (const QString &sub_dir_name, sub_dirs) {
            const QString subSource  = source +"/" + sub_dir_name;
            const QString subCible = cible +"/" + sub_dir_name;
            crypted = cryptDirWithCount(subSource, subCible,crypted,key);
            QCoreApplication::processEvents();
        }
    } else {
        cryptMan.cryptFile(source.toStdString(), cible.toStdString(), key);
        crypted++;
    }
    emit(cryptInProgress(crypted,totalDataCount));
    return crypted;
}

bool CompressCrypt::decryptDir(const QString &source,const QString &cible,  char* key){

    QDir sourceDir(source);
    if(!sourceDir.exists())
        return false;

    emit(decryptingStarted());

    isBusy = true;
    totalDataCount = countFiles(source,0);

    bool success = decryptDirWithCount(source,cible,0, key) > 0;
    emit(decryptingDone());

    isBusy = false;
    return success;
}

quint64 CompressCrypt::decryptDirWithCount(const QString &source,const QString &cible,quint64 decrypted, char* key){

    QDir sourceDir(source);
    if (sourceDir.exists()) {

        QDir targetDir;
        if (!targetDir.mkpath(cible))
            return -1;

        sourceDir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden);
        QStringList sub_dirs = sourceDir.entryList();

        foreach (const QString &sub_dir_name, sub_dirs) {
            const QString subSource  = source +"/" + sub_dir_name;
            const QString subCible = cible + "/" + sub_dir_name;

            decrypted = decryptDirWithCount(subSource, subCible, decrypted, key);
            QCoreApplication::processEvents();
        }
    } else {
        cryptMan.decryptFile(source.toStdString(), cible.toStdString(), key);
        decrypted++;
    }
    emit(decryptInProgress(decrypted,totalDataCount));
    return decrypted;
}

quint64 CompressCrypt::countFiles(const QString &source, quint64 ctn){

    QFileInfo srcInfo(source);
    if (srcInfo.isDir()) {
        QDir srcDir(source);
        srcDir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden);
        QStringList elements = srcDir.entryList();

        foreach (const QString &el, elements) {
            const QString subEl  = source +"/" + el;
            QFileInfo srcInfo(subEl);
             if (srcInfo.isDir())
                 ctn+=countFiles(subEl);
             else
                 ctn++;
        }
    }
    return ctn;
}

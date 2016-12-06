#include "backup.h"
#include <QJsonObject>

qint16 Backup::cnt = 0;

Backup::Backup(QString nom,QString src,QString trg,QString com)
    :name(nom),sourceDir(src),targetDir(trg),comment(com),id(cnt++)
{}

Backup::~Backup(){}

qint16 Backup::getId() const{
    return id;
}

void Backup::setId(const qint16 i){
    id = i;
}

QString Backup::getName() const{
    return name;
}
void Backup::setName(const QString n) {
    name = n;
}

QString Backup::getSource()const{
    return sourceDir;
}
void Backup::setSource(const QString src){
    sourceDir = src;
}

QString Backup::getTarget()const{
    return targetDir;
}
void Backup::setTarget(const QString trg){
    targetDir = trg;
}

QString Backup::getComent()const{
    return comment;
}
void Backup::setComent(const QString cmt){
    comment = cmt;
}

void Backup::saveBackup (QJsonObject &obj) const{
    obj["id"] = id;
    obj["nom"] = name;
    obj["source"] = sourceDir;
    obj["cible"] = targetDir;
    obj["commentaire"] = comment;
}

void Backup::loadBackup(QJsonObject &obj){
    id =  obj["id"].toInt();
    name =  obj["nom"].toString();
    sourceDir =  obj["source"].toString();
    targetDir =  obj["cible"].toString();
    comment =  obj["commentaire"].toString();
}

void Backup::operator =(const Backup &b) {
    id = b.id;
    name = b.name;
    sourceDir = b.sourceDir;
    targetDir = b.targetDir;
    comment = b.comment;
}


bool operator ==(const Backup &b1,const Backup &b2) {
    bool out = false;
    out &= b1.id == b2.id;
    out &= b1.name == b2.name;
    out &= b1.sourceDir == b2.sourceDir;
    out &= b1.targetDir == b2.targetDir;
    out &= b1.comment == b2.comment;

    return out;
}

bool operator !=(const Backup &b1,const Backup &b2){
    return !(b1 == b2);
}

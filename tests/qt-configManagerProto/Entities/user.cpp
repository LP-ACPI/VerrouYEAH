#include "user.h"
#include <QDebug>
#include <QJsonArray>

//User::User():nom(""),mdp(""){}


User::User(User &u){
    nom = u.getNom();
    mdp = u.getMdp();
    foreach (const Backup bcp, u.backupList) {
        addBackup(bcp);
    }
}

User::User(QString nom, QString mdp):nom(nom),mdp(mdp){}

User::~User(){}

QString User::getNom() const{
    return nom;
}
QString User::getMdp() const{
    return mdp;
}

QList<Backup> User::getBackups() const{
    return backupList;
}

void User::addBackup(const Backup &bc){
    Backup bcp(bc);
    bcp.setId(backupList.count());
    backupList.append(bcp);
}

void User::removeBackup(Backup &bc){
    qDebug() << bc.getId();
    backupList.removeOne(bc);
}


void User::modifyBackup(Backup &bc){

    for (int i=0; i < backupList.size(); i++) {
        if (backupList.at(i).getId() == bc.getId()) {
                    backupList.replace(i, bc);
        }
    }
}

void User::saveUser (QJsonObject &obj) const{
    obj["nom"] = nom;
    obj["pass"] = mdp;
    QJsonArray bcpArray;
    foreach (const Backup bcp, backupList) {
        QJsonObject bcpObject;
        bcp.saveBackup(bcpObject);
        bcpArray.append(bcpObject);
    }
    obj["sauvegardes"] = bcpArray;
}

void User::loadUser(QJsonObject &obj){
    nom = obj["nom"].toString();
    mdp = obj["pass"].toString();
    backupList.clear();

    QJsonArray bcpArray = obj["sauvegardes"].toArray();

    for (int i_bcp= 0; i_bcp < bcpArray.size(); ++i_bcp) {
        QJsonObject bcpObject = bcpArray[i_bcp].toObject();
        Backup bcp;
        bcp.loadBackup(bcpObject);
        backupList.append(bcp);
    }
}

void User::operator=(User &u)  {
    nom = u.nom;
    mdp = u.mdp;
}

bool User::exists(){
    return (nom != "" && mdp !="");
}

//bool operator ==(User &u1,const  User &u2) {
//    return (u1.mdp == u2.mdp && u1.nom == u2.nom);
//}

//bool operator !=(User &u1, const User &u2){
//    return ! (u1 == u2);
//}

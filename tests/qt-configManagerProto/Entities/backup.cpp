#include "backup.h"

qint16 Backup::cnt = 0;

Backup::Backup(QString nom,QString src,QString trg,QString com)
    :name(nom),sourceDir(src),targetDir(trg),comment(com),id(cnt++)
{}

#ifndef FTPTESTS_HPP
#define FTPTESTS_HPP


#define TEST_HOST "ftp://f5-preview.awardspace.net"
#define TEST_USER "2114434"
#define TEST_PASS "verrouyeah1test"

#define TEST_UPLOAD_FILE "../config.json"
#define TEST_UPLOAD_DEST "backpackcloud.dx.am"

#define TEST_DOWNLOAD_FILE "backpackcloud.dx.am/Guide_Rootard.pdf"
#define TEST_DOWNLOAD_DEST "../"

#include <QtCore>
#include "unittest.hpp"
#include "../services/Ftp.h"

class FtpTest {
    static void testTeleversementDeFichier(){
        UnitTest<void*>::insertTitle("Test upload");
        Ftp ftpServUpl;
        ftpServUpl.prepareFtp(TEST_HOST,TEST_USER,TEST_PASS);
        bool upload_result = ftpServUpl.ftpUpload(TEST_UPLOAD_FILE,TEST_UPLOAD_DEST);

        QEventLoop loopUp;
        QObject::connect(&ftpServUpl, SIGNAL(finished()), &loopUp, SLOT(quit()));
        loopUp.exec();
        UnitTest<bool>::assertTrue(upload_result);
    }

    static void testTeleChargementDeFichier() {

        UnitTest<void*>::insertTitle("Test download");
        Ftp ftpServDownl;
        ftpServDownl.prepareFtp(TEST_HOST,TEST_USER,TEST_PASS);
        bool download_result = ftpServDownl.ftpDownload(TEST_DOWNLOAD_FILE,TEST_DOWNLOAD_DEST);

        QEventLoop loopDwn;
        QObject::connect(&ftpServDownl, SIGNAL(finished()), &loopDwn, SLOT(quit()));
        loopDwn.exec();
        UnitTest<bool>::assertTrue(download_result);

    }

public:

    static void executeTests(){

        testTeleChargementDeFichier();
        testTeleversementDeFichier();
    }

};

#endif // FTPTESTS_HPP

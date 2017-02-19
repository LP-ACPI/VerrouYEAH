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

         Ftp::getInstance().prepareFtp(TEST_HOST,TEST_USER,TEST_PASS);
        bool upload_result =  Ftp::getInstance().ftpUpload(TEST_UPLOAD_FILE,TEST_UPLOAD_DEST);

        UnitTest<bool>::assertTrue(upload_result);
    }

    static void testTeleChargementDeFichier() {

        UnitTest<void*>::insertTitle("Test download");
        Ftp::getInstance().prepareFtp(TEST_HOST,TEST_USER,TEST_PASS);
        bool download_result =  Ftp::getInstance().ftpDownload(TEST_DOWNLOAD_FILE,TEST_DOWNLOAD_DEST);

        UnitTest<bool>::assertTrue(download_result);

    }

public:

    static void executeTests(){

        testTeleChargementDeFichier();
        testTeleversementDeFichier();
    }

};

#endif // FTPTESTS_HPP

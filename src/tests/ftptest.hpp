#ifndef FTPTEST_H
#define FTPTEST_H

#define TEST_HOST "f5-preview.awardspace.net"
#define TEST_USER "2114434"
#define TEST_PASS "verrouyeah1test"
#define TEST_UPLOAD_FILE "config.json"
#define TEST_UPLOAD_DEST "backpackcloud.dx.am/config.json"

#include "../services/Ftp.h"
#include "unittest.hpp"

class FtpTest {

    static void testUploadFichier(){
        Ftp ftpServ(TEST_HOST,TEST_USER,TEST_PASS);
        bool upload_result = ftpServ.ftpUpload(TEST_UPLOAD_FILE,TEST_UPLOAD_DEST);

        UnitTest<void*>::insertTitle("Test upload");
        UnitTest<bool>::assertTrue("Upload réussi",upload_result);

    }

public:

    static void executeTests(){
        testUploadFichier();
    }
};

#endif // FTPTEST_H

#ifndef DATATESTS_HPP
#define DATATESTS_HPP


#include <unittest.hpp>
#include <iostream>
#include "../models/Data.h"
#include "../models/Directory.h"
#include "../models/File.h"
#include "json.hpp"

using namespace std;
using json=nlohmann::json;

class DataTest {
    static void testGettersSetters(){
        Directory test_dir_1;
        File test_file_1;
        test_dir_1.setName("test_dir_name");
        test_dir_1.setPath("test_dir_path");
        UnitTest<void*>::insertTitle("Test Dir - File");
        UnitTest<string>::assertEquals("dir_name == 'test_dir_name'","test_dir_name",test_dir_1.getName());
        UnitTest<string>::assertEquals("dir_name == 'test_dir_path'","test_dir_path",test_dir_1.getPath());
        UnitTest<bool>::assertTrue("dir is dir",test_dir_1.isDirData());
        UnitTest<string>::assertEquals("file_name == 'test'","test",test_file_1.getName());
        UnitTest<string>::assertEquals("file_name == 'test'","test",test_file_1.getPath());
        UnitTest<bool>::assertFalse("file is not dir",test_file_1.isDirData());
    }

    static void testOperators(){
        Directory test_dir_1("dir_name_1","dir_path_1");
        File test_file_1("file_name_1","file_path_1");

        Directory test_dir_2 = test_dir_1;
        File test_file_2 = test_file_1;

        UnitTest<string>::assertTrue("test_dir_2 == test_dir_1",test_dir_2 == test_dir_1);
        UnitTest<string>::assertTrue("test_file_2 == 'test_file_1'",test_file_2 == test_file_1);
    }

    static void testAddDataToDir(){
        Directory test_dir_1("dir_name_1","dir_path_1");
        Directory test_dir_2("dir_name_2","dir_path_2");
        Directory test_dir_3("dir_name_3","dir_path_3");
        File test_file_1("file_name_1","file_path_1");
        File test_file_2("file_name_2","file_path_2");
        File test_file_3("file_name_3","file_path_3");

        test_dir_1.addData(&test_file_1);
        test_dir_1.addData(&test_file_2);
        test_dir_2.addData(&test_file_3);
        test_dir_1.addData(&test_dir_2);
        test_dir_1.addData(&test_dir_3);

        Directory test_dir_4;
        test_dir_4 = test_dir_1;

//        json j = test_dir_4.to_json();
//        cout << j.dump(2);
    }

public:
    static void executeTests(){
        testGettersSetters();
        testOperators();
        testAddDataToDir();
    }
};

#endif // DATATESTS_HPP

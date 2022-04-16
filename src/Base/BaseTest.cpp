//
// Created by zhaoyf on 2022/4/9.
//
#include "BaseTest.h"
#include "BaseIO.h"
#include "FormatIO.h"
#include "RegexTest.h"
#include "SmartPointerTest.h"

namespace BaseTest{
    void test()
    {
        BaseIO::test();
        FormatIo::test();
        RegexTest::test();
        SmartPointer::test();
    }
}
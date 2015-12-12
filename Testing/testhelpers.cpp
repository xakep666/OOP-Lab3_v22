#include "testhelpers.h"
#include <QtTest>
#include <QtGlobal>
#include <random>
#include <cmath>
#define TESTING
#define IP(_a,_b,_c,_d) (ulong)((_d)<<24 | (_c)<<16 | (_b)<<8 | (_a))
#include <networkservice.h>

void testHelpers::testIsValidIP() {
    try {
        std::vector<ulong> ips;
        ips.reserve(20);
        for(int i=0;i<20;i++)
            ips.push_back(IP(rand()%3,rand()%255,rand()%255,rand()%3));
        const uint IPSize=32;
        int invalidipsnum = std::count_if(ips.begin(),ips.end(),[](ulong ip){
                if ( (ip&0xFF)==0 || (ip&0xFF)==0xFF)
                    return false;
                if (((ip>>(IPSize-8))&0xFF)==0 || ((ip>>(IPSize-8))&0xFF)==0xFF)
                    return false;
                return true;
        });
        int invalidipsregistered = std::count_if(ips.begin(),ips.end(),[](ulong ip){
            return NetworkService::isValidIP(ip);
        });
        QCOMPARE(invalidipsnum,invalidipsregistered);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testHelpers::testIPtoString() {
    try {
        std::string ipstr("192.168.1.1");
        ulong ipulong=IP(192,168,1,1);
        QCOMPARE(NetworkService::LongIPtoString(ipulong),ipstr);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testHelpers::testStringToIP() {
    try {
        std::string ipstr("192.168.1.1");
        ulong ipulong=IP(192,168,1,1);
        QCOMPARE(NetworkService::stringToLongIP(ipstr), ipulong);
        std::string invalidipstr[] = {
            "0.1.2.3",
            "255,1,2,3",
            "1,2,3,0",
            "1,2,3,255",
        };
        for(int i=0;i<4;i++)
            QVERIFY_EXCEPTION_THROWN(NetworkService::stringToLongIP(invalidipstr[i]),std::invalid_argument);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

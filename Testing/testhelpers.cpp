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
        ulong validIP = IP(rand()%254+1,rand()%255,rand()%255,rand()%254+1);
        ulong invalidIP [] = {
            IP(0,rand()%255,rand()%255,rand()%254+1),
            IP(255,rand()%255,rand()%255,rand()%254+1),
            IP(rand()%254+1,rand()%255,rand()%255,0),
            IP(rand()%254+1,rand()%255,rand()%255,255),
        };
        QVERIFY(NetworkService::isValidIP(validIP));
        for(int i=0;i<4;i++) {
            QVERIFY(!NetworkService::isValidIP(invalidIP[i]));
        }
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

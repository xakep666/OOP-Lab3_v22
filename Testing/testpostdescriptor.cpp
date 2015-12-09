#include "testpostdescriptor.h"
#include <QtTest>
#include <QtGlobal>
#include <random>
#include <cmath>
#define TESTING
#define IP(_a,_b,_c,_d) (ulong)((_a)<<24 | (_b)<<16 | (_c)<<8 | (_d))
#include <networkservice.h>
void testPostDescriptor::testConstructor() {
    try {
        NetworkService::PostDescriptor pd;
        time_t cur_time = Time::to_time_t(ftimepoint(Time::now()));
        QCOMPARE(pd.addr,0ul);
        QVERIFY2(abs(cur_time-Time::to_time_t(pd.linktime))<1000*ms::period::num/ms::period::den,"Empty constructor must set linktime to Time::now()");
    } catch (...){
        QFAIL("Unchecked exception thrown");
    }
}

void testPostDescriptor::testParametricConstructor() {
    try {
        ulong dstaddr = IP(192,168,1,1);
        NetworkService::Direction directs[] = {NetworkService::SEND,NetworkService::RECV};
        NetworkService::Direction d = directs[rand()%sizeof(directs)/sizeof(directs[0])];
        ulong traffic = (ulong)random();
        ftimepoint linktime(Time::now());
        NetworkService::Server srv(IP(192,168,2,1));
        NetworkService::PostDescriptor pd(traffic,d,dstaddr,linktime,&srv);
        QCOMPARE(pd.addr,dstaddr);
        QCOMPARE(pd.traffic,traffic);
        QCOMPARE(pd.direction,d);
        QCOMPARE(pd.linktime,linktime);
        QCOMPARE(pd.server,&srv);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testPostDescriptor::testSettingAddress() {
    try {
        NetworkService::PostDescriptor pd;
        ulong validaddr = IP(192,168,1,1);
        pd.setDestinationAddress(validaddr);
        QCOMPARE(pd.addr,validaddr);
        ulong invalidaddr[] = {
            IP(0,1,2,3),
            IP(1,2,3,0),
            IP(255,1,2,3),
            IP(1,2,3,255)
        };
        for(int i=0;i<4;i++) {
            QVERIFY_EXCEPTION_THROWN(pd.setDestinationAddress(invalidaddr[i]),std::invalid_argument);
            QCOMPARE(pd.addr,validaddr);
        }
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testPostDescriptor::testGettingAddress() {
    try {
        NetworkService::PostDescriptor pd;
        ulong addrtoset = IP(192,168,1,1);
        pd.setDestinationAddress(addrtoset);
        QCOMPARE(pd.getDestinationAddress(),addrtoset);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testPostDescriptor::testSettingLinkTime() {
    try {
        NetworkService::PostDescriptor pd;
        ftimepoint timetoset(Time::now());
        pd.setLinkTime(timetoset);
        QCOMPARE(pd.linktime,timetoset);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testPostDescriptor::testGettingLinkTime() {
    try {
        NetworkService::PostDescriptor pd;
        ftimepoint timetoset(Time::now());
        pd.setLinkTime(timetoset);
        QCOMPARE(pd.getLinkTime(),timetoset);
    } catch (...){
        QFAIL("Unchecked exception thrown");
    }
}

void testPostDescriptor::testSettingServer() {
    try {
        NetworkService::PostDescriptor pd;
        NetworkService::Server srv(IP(192,168,1,1));
        pd.setServer(&srv);
        QCOMPARE(pd.server,&srv);
        QVERIFY_EXCEPTION_THROWN(pd.setServer(nullptr),std::invalid_argument);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testPostDescriptor::testGettingServer() {
    try {
        NetworkService::PostDescriptor pd;
        NetworkService::Server srv(IP(192,168,1,1));
        pd.setServer(&srv);
        QCOMPARE(pd.getServer(),&srv);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testPostDescriptor::testSettingTraffic() {
    try {
        NetworkService::PostDescriptor pd;
        ulong traffic = (ulong)random();
        pd.setTraffic(traffic);
        QCOMPARE(pd.traffic,traffic);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testPostDescriptor::testGettingTraffic() {
    try {
        ulong dstaddr = IP(192,168,1,1);
        NetworkService::Direction directs[] = {NetworkService::SEND,NetworkService::RECV};
        NetworkService::Direction d = directs[rand()%sizeof(directs)/sizeof(directs[0])];
        ulong traffic = (ulong)random();
        ftimepoint linktime(Time::now());
        NetworkService::Server srv(IP(192,168,2,1));
        NetworkService::PostDescriptor pd(traffic,d,dstaddr,linktime,&srv);
        QCOMPARE(pd.getTraffic(),traffic);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testPostDescriptor::testSettingDirection() {
    try {
        NetworkService::Direction directs[] = {NetworkService::SEND,NetworkService::RECV};
        NetworkService::Direction d = directs[rand()%sizeof(directs)/sizeof(directs[0])];
        NetworkService::PostDescriptor pd;
        pd.setDirection(d);
        QCOMPARE(pd.direction,d);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testPostDescriptor::testGettingDirection() {
    try {
        ulong dstaddr = IP(192,168,1,1);
        NetworkService::Direction directs[] = {NetworkService::SEND,NetworkService::RECV};
        NetworkService::Direction d = directs[rand()%sizeof(directs)/sizeof(directs[0])];
        ulong traffic = (ulong)random();
        ftimepoint linktime(Time::now());
        NetworkService::Server srv(IP(192,168,2,1));
        NetworkService::PostDescriptor pd(traffic,d,dstaddr,linktime,&srv);
        QCOMPARE(pd.getDirection(),d);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testPostDescriptor::testGettingType() {
    try {
        NetworkService::PostDescriptor pd;
        QCOMPARE(pd.getType(),std::string("Post"));
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testPostDescriptor::testCalculatingPrice() {
    try {
        NetworkService::Server srv(IP(192,168,1,1));
        ulong costpermb = std::round(sqrt(rand()));
        srv.setCostPerMB(costpermb);
        ulong traffic = std::round(sqrt(rand()));
        NetworkService::PostDescriptor pd;
        pd.setServer(&srv);
        pd.setTraffic(traffic);
        QCOMPARE(pd.calculatePrice(),traffic*costpermb);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

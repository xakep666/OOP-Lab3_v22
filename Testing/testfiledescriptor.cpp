#include "testfiledescriptor.h"
#include <QtTest>
#include <QtGlobal>
#include <random>
#include <cmath>
#define TESTING
#define IP(_a,_b,_c,_d) (ulong)((_a)<<24 | (_b)<<16 | (_c)<<8 | (_d))
#include <networkservice.h>

void testFileDescriptor::testConstructor() {
    try {
        NetworkService::FileDescriptor fd;
        time_t cur_time = Time::to_time_t(ftimepoint(Time::now()));
        QCOMPARE(fd.addr,0ul);
        QVERIFY2(abs(cur_time-Time::to_time_t(fd.linktime))<1000*ms::period::num/ms::period::den,"Empty constructor must set linktime to Time::now()");
    } catch (...){
        QFAIL("Unchecked exception thrown");
    }
}

void testFileDescriptor::testParametricConstructor() {
    try {
        ulong dstaddr = IP(192,168,1,1);
        NetworkService::Direction directs[] = {NetworkService::SEND,NetworkService::RECV};
        NetworkService::Direction d = directs[rand()%sizeof(directs)/sizeof(directs[0])];
        ulong traffic = (ulong)random();
        ftimepoint linktime(Time::now());
        NetworkService::Server srv(IP(192,168,2,1));
        fduration duration((ulong)rand());
        NetworkService::FileDescriptor fd(traffic,d,dstaddr,linktime,duration,&srv);
        QCOMPARE(fd.addr,dstaddr);
        QCOMPARE(fd.traffic,traffic);
        QCOMPARE(fd.direction,d);
        QCOMPARE(fd.linktime,linktime);
        QCOMPARE(fd.server,&srv);
        QCOMPARE(fd.linkduration,duration);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testFileDescriptor::testSettingAddress() {
    try {
        NetworkService::FileDescriptor fd;
        ulong validaddr = IP(192,168,1,1);
        fd.setDestinationAddress(validaddr);
        QCOMPARE(fd.addr,validaddr);
        ulong invalidaddr[] = {
            IP(0,1,2,3),
            IP(1,2,3,0),
            IP(255,1,2,3),
            IP(1,2,3,255)
        };
        for(int i=0;i<4;i++) {
            QVERIFY_EXCEPTION_THROWN(fd.setDestinationAddress(invalidaddr[i]),std::invalid_argument);
            QCOMPARE(fd.addr,validaddr);
        }
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testFileDescriptor::testGettingAddress() {
    try {
        NetworkService::FileDescriptor fd;
        ulong addrtoset = IP(192,168,1,1);
        fd.setDestinationAddress(addrtoset);
        QCOMPARE(fd.getDestinationAddress(),addrtoset);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testFileDescriptor::testSettingLinkTime() {
    try {
        NetworkService::FileDescriptor fd;
        ftimepoint timetoset(Time::now());
        fd.setLinkTime(timetoset);
        QCOMPARE(fd.linktime,timetoset);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testFileDescriptor::testGettingLinkTime() {
    try {
        NetworkService::FileDescriptor fd;
        ftimepoint timetoset(Time::now());
        fd.setLinkTime(timetoset);
        QCOMPARE(fd.getLinkTime(),timetoset);
    } catch (...){
        QFAIL("Unchecked exception thrown");
    }
}

void testFileDescriptor::testSettingServer() {
    try {
        NetworkService::FileDescriptor fd;
        NetworkService::Server srv(IP(192,168,1,1));
        fd.setServer(&srv);
        QCOMPARE(fd.server,&srv);
        QVERIFY_EXCEPTION_THROWN(fd.setServer(nullptr),std::invalid_argument);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testFileDescriptor::testGettingServer() {
    try {
        NetworkService::FileDescriptor fd;
        NetworkService::Server srv(IP(192,168,1,1));
        fd.setServer(&srv);
        QCOMPARE(fd.getServer(),&srv);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testFileDescriptor::testSettingTraffic() {
    try {
        NetworkService::FileDescriptor fd;
        ulong traffic = (ulong)random();
        fd.setTraffic(traffic);
        QCOMPARE(fd.traffic,traffic);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testFileDescriptor::testGettingTraffic() {
    try {
        ulong traffic = (ulong)random();
        NetworkService::FileDescriptor fd;
        fd.setTraffic(traffic);
        QCOMPARE(fd.getTraffic(),traffic);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testFileDescriptor::testSettingDirection() {
    try {
        NetworkService::Direction directs[] = {NetworkService::SEND,NetworkService::RECV};
        NetworkService::Direction d = directs[rand()%sizeof(directs)/sizeof(directs[0])];
        NetworkService::FileDescriptor fd;
        fd.setDirection(d);
        QCOMPARE(fd.direction,d);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testFileDescriptor::testGettingDirection() {
    try {
        NetworkService::Direction directs[] = {NetworkService::SEND,NetworkService::RECV};
        NetworkService::Direction d = directs[rand()%sizeof(directs)/sizeof(directs[0])];
        NetworkService::FileDescriptor fd;
        fd.setDirection(d);
        QCOMPARE(fd.getDirection(),d);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testFileDescriptor::testGettingType() {
    try {
        NetworkService::FileDescriptor fd;
        QCOMPARE(fd.getType(),std::string("File"));
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testFileDescriptor::testSettingLinkDuration() {
    try {
        fduration duration(rand());
        NetworkService::FileDescriptor fd;
        fd.setLinkDuration(duration);
        QCOMPARE(fd.linkduration,duration);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testFileDescriptor::testGettingLinkDuration() {
    try {
        fduration duration(rand());
        NetworkService::FileDescriptor fd;
        fd.setLinkDuration(duration);
        QCOMPARE(fd.getLinkDuration(),duration);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testFileDescriptor::testCalculatingPrice() {
    try {
        NetworkService::Server srv(IP(192,168,1,1));
        ulong costpermb = std::round(sqrt(rand()));
        ulong costpermin = std::round(sqrt(rand()));
        srv.setCostPerMB(costpermb);
        srv.setCostPerMin(costpermin);
        ulong traffic = std::round(sqrt(rand()));
        fduration duration(std::round(sqrt(rand())));
        NetworkService::FileDescriptor fd;
        fd.setServer(&srv);
        fd.setTraffic(traffic);
        fd.setLinkDuration(duration);
        QCOMPARE(fd.calculatePrice(),traffic*costpermb+(ulong)(duration.count()*minute_k)*costpermin);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

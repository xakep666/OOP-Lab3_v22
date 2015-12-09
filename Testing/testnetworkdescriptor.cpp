#include "testnetworkdescriptor.h"
#include <QtTest>
#include <QtGlobal>
#include <random>
#include <cmath>
#define TESTING
#define IP(_a,_b,_c,_d) (ulong)((_a)<<24 | (_b)<<16 | (_c)<<8 | (_d))
#include <networkservice.h>

void testNetworkDescriptor::testConstructor() {
    try {
        NetworkService::NetworkDescriptor nd;
        time_t cur_time = Time::to_time_t(ftimepoint(Time::now()));
        QCOMPARE(nd.addr,0ul);
        QVERIFY2(abs(cur_time-Time::to_time_t(nd.linktime))<1000*ms::period::num/ms::period::den,"Empty constructor must set linktime to Time::now()");
    } catch (...){
        QFAIL("Unchecked exception thrown");
    }
}

void testNetworkDescriptor::testParametricConstructor() {
    try {
        ulong dstaddr = IP(192,168,1,1);
        ulong intraffic = random()/2ul;
        ulong outtraffic = random()/2ul;
        ftimepoint linktime(Time::now());
        NetworkService::Server srv(IP(192,168,2,1));
        nduration duration((ulong)rand());
        NetworkService::NetworkDescriptor nd(intraffic,outtraffic,dstaddr,linktime,duration,&srv);
        QCOMPARE(nd.addr,dstaddr);
        QCOMPARE(nd.intraffic,intraffic);
        QCOMPARE(nd.outtraffic,outtrafafic);
        QCOMPARE(nd.linktime,linktime);
        QCOMPARE(nd.server,&srv);
        QCOMPARE(nd.linkduration,duration);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testNetworkDescriptor::testSettingAddress() {
    try {
        NetworkService::NetworkDescriptor nd;
        ulong validaddr = IP(192,168,1,1);
        nd.setDestinationAddress(validaddr);
        QCOMPARE(nd.addr,validaddr);
        ulong invalidaddr[] = {
            IP(0,1,2,3),
            IP(1,2,3,0),
            IP(255,1,2,3),
            IP(1,2,3,255)
        };
        for(int i=0;i<4;i++) {
            QVERIFY_EXCEPTION_THROWN(nd.setDestinationAddress(invalidaddr[i]),std::invalid_argument);
            QCOMPARE(nd.addr,validaddr);
        }
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testNetworkDescriptor::testGettingAddress() {
    try {
        NetworkService::NetworkDescriptor nd;
        ulong addrtoset = IP(192,168,1,1);
        nd.setDestinationAddress(addrtoset);
        QCOMPARE(nd.getDestinationAddress(),addrtoset);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testNetworkDescriptor::testSettingLinkTime() {
    try {
        NetworkService::NetworkDescriptor nd;
        ftimepoint timetoset(Time::now());
        nd.setLinkTime(timetoset);
        QCOMPARE(nd.linktime,timetoset);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testNetworkDescriptor::testGettingLinkTime() {
    try {
        NetworkService::NetworkDescriptor nd;
        ftimepoint timetoset(Time::now());
        nd.setLinkTime(timetoset);
        QCOMPARE(nd.getLinkTime(),timetoset);
    } catch (...){
        QFAIL("Unchecked exception thrown");
    }
}

void testNetworkDescriptor::testSettingServer() {
    try {
        NetworkService::NetworkDescriptor nd;
        NetworkService::Server srv(IP(192,168,1,1));
        nd.setServer(&srv);
        QCOMPARE(nd.server,&srv);
        QVERIFY_EXCEPTION_THROWN(nd.setServer(nullptr),std::invalid_argument);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testNetworkDescriptor::testGettingServer() {
    try {
        NetworkService::NetworkDescriptor nd;
        NetworkService::Server srv(IP(192,168,1,1));
        nd.setServer(&srv);
        QCOMPARE(nd.getServer(),&srv);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testNetworkDescriptor::testSettingOutTraffic() {
    try {
        ulong outtraffic = (ulong)random();
        NetworkService::NetworkDescriptor nd;
        nd.setOutTraffic(outtraffic);
        QCOMPARE(nd.outraffic,intraffic);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testNetworkDescriptor::testGettingOutTraffic() {
    try {
        ulong outtraffic = (ulong)random();
        NetworkService::NetworkDescriptor nd;
        nd.setInTraffic(outraffic);
        QCOMPARE(nd.getOutTraffic(),outraffic);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testNetworkDescriptor::testSettingInTraffic() {
    try {
        ulong intraffic = (ulong)random();
        NetworkService::NetworkDescriptor nd;
        nd.setInTraffic(intraffic);
        QCOMPARE(nd.intraffic,intraffic);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testNetworkDescriptor::testGettingInTraffic() {
    try {
        ulong intraffic = (ulong)random();
        NetworkService::NetworkDescriptor nd;
        nd.setInTraffic(intraffic);
        QCOMPARE(nd.getInTraffic(),intraffic);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testNetworkDescriptor::testGettingType() {
    try {
        NetworkService::NetworkDescriptor nd;
        QCOMPARE(nd.getType(),std::string("File"));
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testNetworkDescriptor::testSettingLinkDuration() {
    try {
        nduration duration(rand());
        NetworkService::NetworkDescriptor nd;
        nd.setLinkDuration(duration);
        QCOMPARE(nd.linkduration,duration);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testNetworkDescriptor::testGettingLinkDuration() {
    try {
        nduration duration(rand());
        NetworkService::NetworkDescriptor nd;
        nd.setLinkDuration(duration);
        QCOMPARE(nd.getLinkDuration(),duration);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testNetworkDescriptor::testCalculatingPrice() {
    try {
        NetworkService::Server srv(IP(192,168,1,1));
        ulong costpermb = std::round(sqrt(rand()));
        ulong costpermin = std::round(sqrt(rand()));
        srv.setCostPerMB(costpermb);
        srv.setCostPerMin(costpermin);
        ulong traffic = std::round(sqrt(rand()));
        nduration duration(std::round(sqrt(rand())));
        NetworkService::NetworkDescriptor nd;
        nd.setServer(&srv);
        nd.setTraffic(traffic);
        nd.setLinkDuration(duration);
        QCOMPARE(nd.calculatePrice(),traffic*costpermb+(ulong)(duration.count()*minute_k)*costpermin);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}


#include "testserver.h"
#include <QtTest>
#include <QtGlobal>
#include <random>
#include <cmath>
#define TESTING
#define IP(_a,_b,_c,_d) (ulong)((_d)<<24 | (_c)<<16 | (_b)<<8 | (_a))
#include <networkservice.h>

void testServer::testConstructor() {
    try {
        ulong addr = IP(192,168,1,1);
        NetworkService::Server srv(addr);
        QCOMPARE(srv.address,addr);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testServer::testGettingAddress() {
    try {
        ulong addr = IP(192,168,1,1);
        NetworkService::Server srv(addr);
        QCOMPARE(srv.getAddress(),addr);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testServer::testSettingName() {
    try {
        NetworkService::Server srv(IP(192,168,1,1));
        std::string name(std::to_string(rand()));
        srv.setName(name);
        QCOMPARE(srv.name,name);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testServer::testGettingName() {
    try {
        NetworkService::Server srv(IP(192,168,1,1));
        std::string name(std::to_string(rand()));
        srv.setName(name);
        QCOMPARE(srv.getName(),name);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testServer::testSettingCostPerMB() {
    try {
        NetworkService::Server srv(IP(192,168,1,1));
        ulong costpermb = (ulong)random();
        srv.setCostPerMB(costpermb);
        QCOMPARE(srv.costpermb,costpermb);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testServer::testGettingCostPerMB() {
    try {
        NetworkService::Server srv(IP(192,168,1,1));
        ulong costpermb = (ulong)random();
        srv.setCostPerMB(costpermb);
        QCOMPARE(srv.getCostPerMB(),costpermb);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testServer::testSettingCostPerMin() {
    try {
        NetworkService::Server srv(IP(192,168,1,1));
        ulong costpermin = (ulong)random();
        srv.setCostPerMin(costpermin);
        QCOMPARE(srv.costpermin,costpermin);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

void testServer::testGettingCostPerMin() {
    try {
        NetworkService::Server srv(IP(192,168,1,1));
        ulong costpermin = (ulong)random();
        srv.setCostPerMin(costpermin);
        QCOMPARE(srv.getCostPerMin(),costpermin);
    } catch (...) {
        QFAIL("Unchecked exception thrown");
    }
}

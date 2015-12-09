#ifndef TESTPOSTDESCRIPTOR_H
#define TESTPOSTDESCRIPTOR_H
#include <QtTest>
class testPostDescriptor : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testConstructor();
    void testSettingAddress();
    void testGettingAddress();
    void testSettingLinkTime();
    void testGettingLinkTime();
    void testSettingServer();
    void testGettingServer();
    void testParametricConstructor();
    void testSettingDirection();
    void testGettingDirection();
    void testSettingTraffic();
    void testGettingTraffic();
    void testGettingType();
    void testCalculatingPrice();
};

#endif // TESTPOSTDESCRIPTOR_H

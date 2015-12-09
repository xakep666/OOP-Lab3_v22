#ifndef TESTNETWORKDESCRIPTOR
#define TESTNETWORKDESCRIPTOR
#include <QtTest>
class testNetworkDescriptor : public QObject {
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
    void testSettingInTraffic();
    void testGettingInTraffic();
    void testSettingOutTraffic();
    void testGettingOutTraffic();
    void testGettingType();
    void testSettingLinkDuration();
    void testGettingLinkDuration();
    void testCalculatingPrice();
};
#endif // TESTNETWORKDESCRIPTOR


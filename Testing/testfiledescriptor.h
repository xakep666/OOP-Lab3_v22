#ifndef TESTFILEDESCRIPTOR
#define TESTFILEDESCRIPTOR
#include <QtTest>
class testFileDescriptor : public QObject {
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
    void testSettingLinkDuration();
    void testGettingLinkDuration();
    void testCalculatingPrice();
};

#endif // TESTFILEDESCRIPTOR


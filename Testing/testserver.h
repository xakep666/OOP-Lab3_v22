#ifndef TESTSERVER
#define TESTSERVER
#include <QtTest>
class testServer : public QObject {
    Q_OBJECT
private Q_SLOTS:
    void testConstructor();
    void testGettingAddress();
    void testSettingName();
    void testGettingName();
    void testSettingCostPerMB();
    void testGettingCostPerMB();
    void testSettingCostPerMin();
    void testGettingCostPerMin();
};

#endif // TESTSERVER


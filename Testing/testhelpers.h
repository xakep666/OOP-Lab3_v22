#ifndef TESTHELPERS
#define TESTHELPERS
#include <QtTest>
class testHelpers : public QObject {
    Q_OBJECT
private Q_SLOTS:
    void testIsValidIP();
    void testStringToIP();
    void testIPtoString();
};
#endif // TESTHELPERS


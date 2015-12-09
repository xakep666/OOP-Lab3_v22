#include <QString>
#include <QtTest>

class Testing : public QObject
{
    Q_OBJECT

public:
    Testing();

private Q_SLOTS:
    void testCase1();
};

Testing::Testing()
{
}

void Testing::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(Testing)

#include "testing.moc"

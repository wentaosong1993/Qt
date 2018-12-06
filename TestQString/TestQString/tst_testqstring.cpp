#include <QString>
#include <QtTest>

class TestQString : public QObject
{
    Q_OBJECT

public:
    TestQString();

private Q_SLOTS:
    void testToLower();
    void testToLower_data();
};

TestQString::TestQString()
{
}

void TestQString::testToLower_data()
{
    //添加测试列
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");

    //添加测试数据
    QTest::newRow("lower")<<"hello"<<"hello";
    QTest::newRow("mixed")<<"heLLo"<<"hello";
    QTest::newRow("upper")<<"HELLO"<<"hello";
}

void TestQString::testToLower()
{
    QFETCH(QString,string);
    QFETCH(QString,result);

    QCOMPARE(string.toLower(),result);
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestQString)

#include "tst_testqstring.moc"

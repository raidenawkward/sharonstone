#include "testprintclass.h"
#include <QString>
#include <QObject>
#include <QDebug>

TestPrintClass::TestPrintClass()
{
    _date = QDateTime::currentDateTime();
}

QString TestPrintClass::getHeader() const
{
    return _header;
}

void TestPrintClass::setHeader(const QString& header)
{
    _header = header;
}

void TestPrintClass::addItem(const QString& value)
{
    _list.append(value);
}

QString TestPrintClass::getItem(int index) const
{
    return _list[index];
}

int TestPrintClass::getItemCount() const
{
    return _list.count();
}

static int g_id = 0;

#define MAX_LIST_ITEM_COUNT (8)

TestPrintClass* TestPrintClass::create()
{
    TestPrintClass* res = new TestPrintClass();

    res->setDate(QDateTime::currentDateTime());
    res->setHeader(QString("这里是测试 CLASS ").append((QString::number(g_id))));

    res->setObject(QString("TestPrintClass"));
    res->setTitle(res->getObject());

    qsrand(res->getDate().toTime_t());
    int rand = qrand() % MAX_LIST_ITEM_COUNT;

    for (int i = 0; i < rand; ++i) {
        res->addItem(QString("this is item ").append(QString::number(i)).append(" in TestPrintClass"));
    }

    ++g_id;

    return res;
}

#include "testprintclass.h"

TestPrintClass::TestPrintClass()
{
    _date = QDateTime::currentDateTime();
}

void TestPrintClass::addItem(const QString& key, const QString& value)
{
    _list.insert(key, value);
}

QString TestPrintClass::getItem(const QString& key)
{
    return _list[key];
}

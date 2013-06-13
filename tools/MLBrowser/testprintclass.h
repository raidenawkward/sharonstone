#ifndef TESTPRINTCLASS_H
#define TESTPRINTCLASS_H

#include <QString>
#include <QHash>
#include <QDateTime>

class TestPrintClass
{
public:
    TestPrintClass();

    QString getTitle() { return _title; }
    void setTitle(const QString& title) { _title = title; }
    QString getHeader() { return _header; }
    void setHeader(const QString& header) { _header = header; }
    QString getObject() { return _object; }
    void setObject(const QString& object) { _object = object; }
    QDateTime getDate() { return _date; }
    void setDate(const QDateTime& date) { _date = date; }

    void addItem(const QString& key, const QString& value);
    QString getItem(const QString& key);

private:
    QString _title;
    QString _header;
    QString _object;
    QDateTime _date;
    QHash<QString, QString> _list;
};

#endif // TESTPRINTCLASS_H

#ifndef TESTPRINTCLASS_H
#define TESTPRINTCLASS_H

#include <QString>
#include <QHash>
#include <QDateTime>
#include <QStringList>


class TestPrintClass
{
public:
    TestPrintClass();

    QString getTitle() const { return _title; }
    void setTitle(const QString& title) { _title = title; }
    QString getHeader() const;
    void setHeader(const QString& header);
    QString getObject() const { return _object; }
    void setObject(const QString& object) { _object = object; }
    QDateTime getDate() const { return _date; }
    void setDate(const QDateTime& date) { _date = date; }

    void addItem(const QString& value);
    QString getItem(int index) const;
    int getItemCount() const;

    static TestPrintClass* create();

private:
    QString _title;
    QString _header;
    QString _object;
    QDateTime _date;
    QStringList _list;
};

#endif // TESTPRINTCLASS_H

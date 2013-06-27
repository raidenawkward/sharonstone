#include "qtdatavisitor.h"
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>


QtDataVisitor::QtDataVisitor()
    : _query(NULL)
{
    this->setDatabase(NULL);
}

QtDataVisitor::QtDataVisitor(SSDatabase* db)
    : _query(NULL)
{
    this->setDatabase(db);
}

QtDataVisitor::~QtDataVisitor()
{
    if (_query) {
        _query->clear();
        delete _query;
    }
}

QString QtDataVisitor::loadWhereFromCond(SSVisitCondition* cond)
{
    QString where;

    if (!cond)
        return where;

    int count = cond->getMemberCount();

    for (int i = 0; i < count; ++i) {
        QString title = cond->getMemberName(i).c_str();
        QString value = cond->getMemberValue(i).c_str();

        if (!value.isEmpty() && !title.isEmpty()) {
            if (!where.isEmpty())
                where.append(" and ");

            where.append(title)
                    .append("='")
                    .append(value)
                    .append("'");
        }
    }

    if (!where.isEmpty())
        where.prepend(" where ");

    return where;
}

bool QtDataVisitor::add(SSVisitCondition* dest)
{
    if (!_query)
        return false;

    if (!dest)
        return false;

    QString command = QString("insert into ")
            .append(dest->getContainerName().c_str());

    QString titleList;
    QString valueList;
    int count = dest->getMemberCount();

    for (int i = 0; i < count; ++i) {
        QString title = dest->getMemberName(i).c_str();
        QString value = dest->getMemberValue(i).c_str();

        if (!value.isEmpty() && !title.isEmpty()) {
            if (!titleList.isEmpty())
                titleList.append(",");

            titleList.append(title);

            if (!valueList.isEmpty())
                valueList.append(",");
            valueList.append("'").append(value).append("'");
        }
    }

    command.append(" (").append(titleList).append(") ");
    command.append("values (").append(valueList).append(");");

    return _query->exec(command);
}

bool QtDataVisitor::remove(SSVisitCondition* cond)
{
    if (!_query)
        return false;

    if (!cond)
        return false;

    QString command = QString("delete from ")
                .append(cond->getContainerName().c_str());
    QString condition = loadWhereFromCond(cond);

    if (condition.isEmpty())
        return false;

    return _query->exec(command);
}

bool QtDataVisitor::update(SSVisitCondition* cond, SSVisitCondition* dest)
{
    if (!_query)
        return false;

    if (!cond || !dest)
        return false;

    QString command = QString("update ").append(" ").append(dest->getContainerName().c_str());
    QString set;
    int count = 0;

    count = dest->getMemberCount();
    for (int i = 0; i < count; ++i) {
        QString title = dest->getMemberName(i).c_str();
        QString value = dest->getMemberValue(i).c_str();

        if (!value.isEmpty() && !title.isEmpty()) {
            if (!set.isEmpty())
                set.append(",");

            set.append(title)
                    .append("='")
                    .append(value)
                    .append("'");
        }
    }
    command.append(" set ").append(set);

    QString where = loadWhereFromCond(cond);

    if (!where.isEmpty())
        command.append(where);
    command.append(";");

    return _query->exec(command);
}

vector<SSDataProvider*> QtDataVisitor::select(SSVisitCondition* cond)
{
    vector<SSDataProvider*> res;

    if (!_query)
        return res;

    if (!cond)
        return res;

    QString command = QString("select * from ").append(cond->getContainerName().c_str());
    QString where = loadWhereFromCond(cond);

    if (!where.isEmpty())
        command.append(where);
    command.append(";");

    if (!_query->exec(command))
        return res;

    QSqlRecord record = _query->record();
    for (int i = 0; i < record.count(); ++i) {
        SSDataProvider* item = cond->clone();
        if (!item)
            return res;

        item->setMemberValue(record.fieldName(i).toStdString()
                             , record.value(i).toString().toStdString());
        res.push_back(item);
    }

    return res;
}

int QtDataVisitor::count(SSVisitCondition* cond)
{
    if (!_query)
        return 0;

    if (!cond)
        return 0;

    QString command = QString("select count(*) from ").append(cond->getContainerName().c_str());
    QString where = loadWhereFromCond(cond);

    if (!where.isEmpty())
        command.append(where);
    command.append(";");

    if (!_query->exec(command))
        return 0;

    bool ok = false;
    int count = _query->value(0).toInt(&ok);

    if (ok)
        return count;

    return 0;
}

bool QtDataVisitor::exist(SSVisitCondition* dest)
{
    return count(dest) > 0;
}

string QtDataVisitor::error()
{
    if (!_query)
        return string();

    QString res;
    res.append("[last query] \n").append(_query->lastQuery());
    res.append("[last error] \n").append(_query->lastError().text());

    return res.toStdString();
}

void QtDataVisitor::setDatabase(SSDatabase* db)
{
    if (_query) {
        _query->clear();
        delete _query;
    }

    if (!db)
        return;

    QSqlDatabase* database = (QSqlDatabase*)db->databaseInfo();
    _query = new QSqlQuery(*database);
}


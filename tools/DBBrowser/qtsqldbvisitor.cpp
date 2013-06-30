#include "qtsqldbvisitor.h"
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>

QtSqlDBVisitor::QtSqlDBVisitor(SSDatabase* db)
    : SSDataVisitor(db)
    , _query(NULL)
{
    setDatabase(db);
}

QtSqlDBVisitor::~QtSqlDBVisitor()
{
    if (_query) {
        _query->clear();
        delete _query;
    }
}

int QtSqlDBVisitor::visit(string cmd)
{
    if (!_query)
        return 0;

    QString strCmd = QString(cmd.c_str());

    return _query->exec(strCmd) ? 1 : 0;
}

vector<SSDataProvider*> QtSqlDBVisitor::visitResult(SSDataProvider* prototype)
{
    vector<SSDataProvider*> res;

    if (!prototype)
        return res;

    if (!_query)
        return res;

    QSqlRecord record = _query->record();
    for (int i = 0; i < record.count(); ++i) {
        SSDataProvider* item = prototype->cloneProvider();
        if (!item)
            return res;

        item->setDataMemberValue(record.fieldName(i).toStdString()
                             , record.value(i).toString().toStdString());
        res.push_back(item);
    }

    return res;
}

void QtSqlDBVisitor::clearResult()
{
    if (!_query)
        return;
    _query->clear();
}

string QtSqlDBVisitor::error()
{
    if (!_query)
        return string();

    QString res;
    res.append("[last query] \n").append(_query->lastQuery());
    res.append("[last error] \n").append(_query->lastError().text());

    return res.toStdString();
}

void QtSqlDBVisitor::setDatabase(SSDatabase* db)
{
    SSDataVisitor::setDatabase(db);

    if (_query) {
        _query->clear();
        delete _query;
    }

    if (!db) {
        _query = NULL;
        return;
    }

    QSqlDatabase* database = (QSqlDatabase*)db->databaseInfo();
    _query = new QSqlQuery(*database);
}

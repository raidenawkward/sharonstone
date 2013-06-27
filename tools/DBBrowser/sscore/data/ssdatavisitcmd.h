/*
 * INTERFACE
 * for data visit query executing
 * based on certain platform
 */

#ifndef SSDATAVISITCMD_H
#define SSDATAVISITCMD_H


#include "sscore/data/ssdatabase.h"
#include "sscore/data/ssdataprovider.h"

#include <string>
#include <vector>

using namespace std;


class SSDataVisitCmd
{
public:
    virtual bool exec() = 0;

    virtual void setQuery(string query) { _query = query; }
    virtual string getQuery() { return _query; }

    virtual vector<SSDataProvider*> result() = 0;
    virtual int getResultCount() = 0;

    virtual setDatabase(SSDatabase* db) { _db = db; }
    virtual SSDatabase* getDatabase() { return _db; }

protected:
    SSDataVisitCmd() {}

private:
    SSDatabase* _db;
    string _query;
};

#endif // SSDATAVISITCMD_H

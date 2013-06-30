/**
 * [INTERFACE]
 * for transforming class members into strings
 * exactly accordant with items in db table
 * similar with Printable
 * would access/modify members of class
 */

#ifndef SSDATAPROVIDER_H
#define SSDATAPROVIDER_H

#include <string>

using namespace std;

#undef SUPPORT_DATAORDER

class SSDataProvider
{
public:

    virtual string getDataMemberName(int type) = 0;
    virtual string getDataMemberValue(int type) = 0;
    virtual string getDataMemberValue(string name) = 0;
    virtual int getDataMemberCount() = 0;

    virtual string setDataMemberValue(string name, string value) = 0;

    /// for table name
    virtual string getDataContainerName() = 0;

    /// just a name
    virtual string getDataName() = 0;

    /// make a copy for provider and inner class
    // may be useful in SSDataVisitor::select()
    virtual SSDataProvider* cloneProvider() = 0;

    /// get inner class instance
    virtual void* dataProvidee() = 0;

protected:
    SSDataProvider() {}
};

#endif // SSDATAPROVIDER_H

/*
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

    virtual string getMemberName(int type) = 0;
    virtual string getMemberValue(int type) = 0;
    virtual int getMemberCount() = 0;

    virtual string setMemberValue(string name, string value) = 0;

    /// for table name
    virtual string getContainerName() = 0;

    /// just a name
    virtual string getName() = 0;

    /// make a copy for provider and inner class
    // may be useful in SSDataVisitor::select()
    virtual SSDataProvider* clone() = 0;

    /// get inner class instance
    virtual void* providee() = 0;

#ifdef SUPPORT_DATAORDER
    /*
     * SSDataOrder
     * class for external condition for visiting
     * for db system,
     * it may present one or more of:
     * 1. range
     * 2. distinct
     * 3. order by
     */
    ///?? for order
    virtual void setDataOrder(SSDataOrder* o) { _order = o; }
    virtual SSDataOrder* getOrder() { return _order; }
#endif

protected:
    SSDataProvider() {}

#ifdef SUPPORT_DATAORDER
private:
    SSDataOrder* _order/*(init on NULL)*/;
#endif
};

#endif // SSDATAPROVIDER_H

/*
 * [INTERFACE]
 * factory for data visitor
 * may use singleton pattern
 */

#ifndef SSDATAVISITORFACTORY_H
#define SSDATAVISITORFACTORY_H


#include "sscore/data/ssdatavisitor.h"
#include "sscore/data/ssdatabasefactory.h"



class SSDataVisitorFactory
{
public:
    virtual static SSDataVisitor* produce(SSDatabaseFactory* dbFactory) = 0;

    /// returns the instance created by produce() last time
    virtual static SSDataVisitor* instance() = 0;
};

#endif // SSDATAVISITORFACTORY_H

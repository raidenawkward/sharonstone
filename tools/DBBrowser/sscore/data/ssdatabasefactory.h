/**
 * [INTERFACE]
 * factory for database connection
 */

#ifndef SSDATABASEFACTORY_H
#define SSDATABASEFACTORY_H


#include "sscore/data/ssdatabase.h"


class SSDatabaseFactory
{
public:
    virtual static SSDatabase* produce() = 0;
    /// returns the instance created by produce() last time
    virtual static SSDatabase* instance() = 0;
};

#endif // SSDATABASEFACTORY_H

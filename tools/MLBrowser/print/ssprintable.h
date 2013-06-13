#ifndef SSPRINTABLE_H
#define SSPRINTABLE_H

class SSPrintable
{
public:
    virtual const char* getPrintableName() const = 0;
    virtual int getPrintableItemCount() = 0;

    virtual const char* getPrintableItemName(int index) = 0;
    virtual const char* getPrintableItemValue(int index) = 0;
    virtual const char* getPrintableItemValue(const char* name) = 0;

protected:
    SSPrintable() {}
};

#endif // SSPRINTABLE_H

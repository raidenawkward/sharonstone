#ifndef SSTEMPLETE_H
#define SSTEMPLETE_H

#include <string>

using namespace std;

class SSTemplete
{
public:
    virtual bool loadTemplete(string path) = 0;
    virtual bool setTagValue(string tag, string value) = 0;
    virtual bool appendTagValue(string tag, string value) = 0;
    virtual bool isTagExist(string tag) = 0;
    virtual string getNextTag() = 0;
    virtual void clearAllTags() = 0;

    virtual void setTagPrefix(string prefix) = 0;
    virtual void setTagSuffix(string suffix) = 0;

protected:
    SSTemplete();
};

#endif // SSTEMPLETE_H

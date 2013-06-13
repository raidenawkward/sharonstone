#ifndef SSTEMPLETE_H
#define SSTEMPLETE_H

class SSTemplete
{
public:
    virtual bool loadTemplete(const char* path) = 0;
    virtual bool setTagValue(const char* tag, const char* value) = 0;
    virtual bool appendTagValue(const char* tag, const char* value) = 0;
    virtual bool isTagExist(const char* tag) = 0;
    virtual const char* getNextTag() = 0;
    virtual void clearAllTags() = 0;

    virtual void setTagPrefix(const char* prefix) = 0;
    virtual void setTagSuffix(const char* suffix) = 0;

protected:
    SSTemplete();
};

#endif // SSTEMPLETE_H

#ifndef TEMPLETEPRINTINGBROWSER_H
#define TEMPLETEPRINTINGBROWSER_H

#include <QTextBrowser>
#include <QString>
#include <QPrinter>

#include "sscore/sstemplete.h"
#include "sscore/print/ssprintimpl.h"
#include "sscore/print/ssprintable.h"


#define TEMPLETEPRINTINGBROWSER_DEFAULT_TAG_PREFIX ("${")
#define TEMPLETEPRINTINGBROWSER_DEFAULT_TAG_SUFFIX ("}")


class TempletePrintingBrowser : public QTextBrowser, public SSTemplete, public SSPrintImpl
{
    Q_OBJECT
public:
    explicit TempletePrintingBrowser(QWidget *parent = 0);
    virtual ~TempletePrintingBrowser();

    bool loadPrintable(const SSPrintable* printable);

    /*
     * methods from SSTemplete
     */
    virtual bool loadTemplete(const char* path);
    virtual bool setTagValue(const char* tag, const char* value);
    virtual bool appendTagValue(const char* tag, const char* value);
    virtual bool isTagExist(const char* tag);
    virtual const char* getNextTag();
    virtual void clearAllTags();

    virtual void setTagPrefix(const char* prefix);
    virtual void setTagSuffix(const char* suffix);

    /*
     * methods from SSPrintImpl
     */
    virtual bool preparePrint();
    virtual bool startPrint();
    virtual void fihishPrint();
    virtual void preview();

private slots:
    void onPreviewRequest(QPrinter* printer);

private:
    QString _templeteContent;
    QString _tagPrefix;
    QString _tagSuffix;

    const SSPrintable* _printable;

    QPrinter *_printer;
};

#endif // TEMPLETEPRINTINGBROWSER_H

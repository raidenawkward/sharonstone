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


class TempletePrintingBrowser : public QTextBrowser, public SSTemplete, public SSPrintImpl, SSPrintable::SSPrintableCallback
{
    Q_OBJECT
public:
    explicit TempletePrintingBrowser(QWidget *parent = 0);
    virtual ~TempletePrintingBrowser();

    /*
     * methods from SSTemplete
     */
    virtual bool loadTemplete(string path);
    virtual bool setTagValue(string tag, string value);
    virtual bool appendTagValue(string tag, string value);
    virtual bool isTagExist(string tag);
    virtual string getNextTag();
    virtual void clearAllTags();

    virtual void setTagPrefix(string prefix);
    virtual void setTagSuffix(string suffix);

    /*
     * methods from SSPrintImpl
     */
    virtual bool preparePrint();
    virtual bool printDoc();
    virtual void fihishPrint();

    virtual bool preparePreview();
    virtual bool preview();
    virtual void finishPreview();

    virtual bool openOptionDialog();

    virtual bool loadPrintable(SSPrintable* printable);

    /*
     * method from SSPrintableCallback
     */
    virtual bool onPrintablePrint(int, string title, string value);

private slots:
    void onPreviewRequest(QPrinter* printer);

private:
    QString _templeteContent;
    QString _tagPrefix;
    QString _tagSuffix;

    SSPrintable* _printable;

    QPrinter *_printer;
};

#endif // TEMPLETEPRINTINGBROWSER_H

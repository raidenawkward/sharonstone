#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "print/ssprintable.h"
#include "print/ssprintimpl.h"
#include "print/ssprinter.h"

#include <QFile>
#include <QFileDialog>
#include <QFontDialog>
#include <QDebug>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>


#define DEFAULT_CONTENT "<tr><td>Welcome</td></tr>"
#define DEFAULT_FOND_SIZE (20)


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _printer = NULL;
}

MainWindow::~MainWindow()
{
    if (_printer)
        delete _printer;

    delete ui;
}


void MainWindow::loadFile(const QString path)
{
    QFile file(path);

    if (!file.open(QFile::ReadOnly)) {
        return;
    }

    QString content = QString(file.readAll().constData());

    ui->textBrowser->setHtml(content);

    _file = path;
}

bool MainWindow::prePrint()
{
    if (_printer)
        delete _printer;

    _printer = new QPrinter();
    _printer->setPageSize(QPrinter::A4);
    _printer->setPageMargins(0,0,0,0,QPrinter::Millimeter);

    return true;
}

void MainWindow::print()
{
    if (!_printer)
        return;

    QPrintDialog dialog(_printer, this);

    if (dialog.exec() != QDialog::Accepted)
        return;

    ui->textBrowser->print(_printer);
}

void MainWindow::onPreviewRequest(QPrinter* printer)
{
    ui->textBrowser->print(printer);
}

void MainWindow::on_actionAbout_triggered()
{

}

void MainWindow::on_actionOpen_triggered()
{
    QString filepath = QFileDialog::getOpenFileName(this);
    loadFile(filepath);
}

void MainWindow::on_actionRefresh_triggered()
{
    loadFile(_file);
}

void MainWindow::on_actionPrint_triggered()
{
    if (prePrint())
        print();
}

void MainWindow::on_actionPreview_triggered()
{
    QPrintPreviewDialog dialog(_printer, this);
    connect(&dialog, SIGNAL(paintRequested(QPrinter *)), this, SLOT(onPreviewRequest(QPrinter *)));
    dialog.exec();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionFont_triggered()
{
    bool ok = false;

    QFont font = QFontDialog::getFont(&ok, this);

    if (!ok)
        return;

    ui->textBrowser->setFont(font);
}

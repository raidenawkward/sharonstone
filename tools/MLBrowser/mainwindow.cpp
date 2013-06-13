#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sscore/print/ssprintable.h"
#include "sscore/print/ssprintimpl.h"
#include "sscore/print/ssprinter.h"

#include <QFileDialog>
#include <QFontDialog>


#define DEFAULT_CONTENT "<tr><td>Welcome</td></tr>"
#define DEFAULT_FOND_SIZE (20)


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _printer(NULL)
{
    ui->setupUi(this);

    _printer = new SSPrinter(ui->printingBrowser);
}

MainWindow::~MainWindow()
{
    if (_printer)
        delete _printer;

    delete ui;
}


void MainWindow::loadFile(const QString path)
{
    ui->printingBrowser->loadTemplete(path.toUtf8().constData());
}

void MainWindow::on_actionAbout_triggered()
{

}

void MainWindow::on_actionOpen_triggered()
{
    QString filepath = QFileDialog::getOpenFileName(this);
    loadFile(filepath);
    _file = filepath;
}

void MainWindow::on_actionRefresh_triggered()
{
    loadFile(_file);
}

void MainWindow::on_actionPrint_triggered()
{
    if (!_printer)
        return;

    _printer->print();
}

void MainWindow::on_actionPreview_triggered()
{
    if (!_printer)
        return;

    _printer->preview();
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

    ui->printingBrowser->setFont(font);
}

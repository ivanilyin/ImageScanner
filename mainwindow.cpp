#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "imagesmodel.h"
#include <QtGui>

#include "imagecreatorthread.h"

const int MainWindow::cIconSize = 64;
const int MainWindow::cGridSize = 80;

QList<thumb> createList()
{
    QList<thumb> result;

    thumb same;
    same.pixmap = QImage("/home/luxa/Pictures/Icons/ninja.png")
                            .scaled(QSize(MainWindow::cIconSize, MainWindow::cIconSize), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    same.name = "ololo";

    for (int i = 0; i < 1000; i++) {
        result << same;
    }

    return result;
}




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listView->setGridSize(QSize(cGridSize, cGridSize));
    ui->listView->setIconSize(QSize(cIconSize, cIconSize));

    QList<thumb> *testList = new QList<thumb>(/*createList()*/);

    model = new ImagesModel(testList, this);

    ui->listView->setModel(model);

    mProgressBar = new QProgressBar();
    mProgressBar->setMinimum(0);
    mProgressBar->setValue(0);
    mProgressBar->setVisible(false);

    ui->statusBar->addPermanentWidget(mProgressBar);

    qRegisterMetaType<thumb>("thumb");
    connect(&mThread, SIGNAL(sendThumb(thumb)), this, SLOT(addItem(thumb)));
    connect(&mThread, SIGNAL(maxFilesCountEvaluated(int)), mProgressBar, SLOT(setMaximum(int)));
    connect(&mThread, SIGNAL(scanFinished()), mProgressBar, SLOT(hide()));

    mThread.compute("/home/luxa/Pictures/Photos");
}

void MainWindow::addItem(thumb pThumb)
{
    model->addItem(pThumb);
    mProgressBar->setValue(mProgressBar->value() + 1);
    if (!mProgressBar->isVisible()) {
        mProgressBar->setVisible(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

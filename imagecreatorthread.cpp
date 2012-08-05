#include "imagecreatorthread.h"
#include "imagesmodel.h"
#include "mainwindow.h"

#include <QtGui>

void ImageCreatorThread::scanFS(const QString &pPath)
{
    Q_ASSERT(QFileInfo(pPath).exists());

    QDir rootDir(pPath);

    int counter = 0;
    foreach (QFileInfo fInfo, rootDir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot)) {
        if (restart) {
            break;
        }

        if (fInfo.isFile()) {
            if (fInfo.suffix() == "jpeg"
            || fInfo.suffix() == "jpg"
            || fInfo.suffix() == "JPG"
            || fInfo.suffix() == "png") {
                thumb tmpThumb;
                tmpThumb.name = fInfo.fileName().right(5);
                QImage testPixmap = QImage(fInfo.absoluteFilePath());

                if (testPixmap.isNull()) {
                    counter++;
                    qDebug() << "can't create pixmap for" << fInfo.absoluteFilePath();
                } else {
                    tmpThumb.pixmap = testPixmap.scaled(QSize(MainWindow::cIconSize, MainWindow::cIconSize)
                                                ,Qt::KeepAspectRatio, Qt::SmoothTransformation);

                    emit sendThumb(tmpThumb);
                }

            }

        } else if (fInfo.isDir()) {
            scanFS(fInfo.filePath());
        }
    }
}

int ImageCreatorThread::fsCount(const QString &pPath)
{
    Q_ASSERT(QFileInfo(pPath).exists());

    QDir rootDir(pPath);

    QStringList nameFilters;
    nameFilters << "*";

    int fileCount = 0;

    foreach (QFileInfo fInfo, rootDir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot)) {

        if (fInfo.isFile()) {
            if (fInfo.suffix() == "jpeg"
            || fInfo.suffix() == "jpg"
            || fInfo.suffix() == "JPG"
            || fInfo.suffix() == "png") {
                fileCount++;
            }

        } else if (fInfo.isDir()) {
            fileCount += fsCount(fInfo.filePath());
        }
    }

    return fileCount;
}


ImageCreatorThread::ImageCreatorThread(QObject *parent) :
QThread(parent)
{
    restart = false;
    abort = false;
}

void ImageCreatorThread::compute(const QString &pStr)
{
    QMutexLocker curLocker(&mMutex);

    mScanningPath = pStr;

    if (!isRunning()) {
        start(LowPriority);
    } else {
        restart = true;
        mWaitCondition.wakeOne();
    }
}

void ImageCreatorThread::run()
{
    forever {
        qDebug() << "Custom thread started execution";

        mMutex.lock();
        QString searchStr = mScanningPath;
        mMutex.unlock();

        if (abort) {
            return;
        }
        if (restart) {
            break;
        }

        QTime curTime = QTime::currentTime();
        int fsCnt = fsCount(searchStr);
        int msecsto = curTime.msecsTo(QTime::currentTime());
        qDebug() << "time on evaluation" << msecsto;

        emit maxFilesCountEvaluated(fsCnt);

        emit scanStarted();
        scanFS(searchStr);
        emit scanFinished();

        mMutex.lock();
        if (!restart) {
            mWaitCondition.wait(&mMutex);
        }
        restart = false;
        mMutex.unlock();

    }
}

ImageCreatorThread::~ImageCreatorThread()
{
    qDebug() <<  "thread destructor catched";

    mMutex.lock();
    abort = true;
    mWaitCondition.wakeOne();
    mMutex.unlock();

    wait();
}

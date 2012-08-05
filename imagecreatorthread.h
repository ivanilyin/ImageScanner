#ifndef IMAGECREATORTHREAD_H
#define IMAGECREATORTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "imagesmodel.h"

class ImageCreatorThread : public QThread
{
    Q_OBJECT
public:
    explicit ImageCreatorThread(QObject *parent = 0);
    ~ImageCreatorThread();
        void compute(const QString &pStr);


protected:
    void run();
    
signals:
    void sendThumb(thumb pThumb);
    void sendImage(QImage image);
    void scanStarted();
    void scanFinished();
    void maxFilesCountEvaluated(int max);

    
public slots:

private:
    void scanFS(const QString &pPath);
    int fsCount(const QString &pPath);

private:
    QMutex mMutex;
    QWaitCondition mWaitCondition;
    QString mScanningPath;
    bool restart;
    bool abort;
    
};

#endif // IMAGECREATORTHREAD_H

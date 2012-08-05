#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "imagecreatorthread.h"

class ImagesModel;
class QProgressBar;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static const int cIconSize;
    static const int cGridSize;

public slots:
    void addItem(thumb pThumb);
    
private:
    Ui::MainWindow *ui;
    ImageCreatorThread mThread;
    ImagesModel *model;
    QProgressBar *mProgressBar;
};

#endif // MAINWINDOW_H

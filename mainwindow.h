#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "IViewer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        Ui::MainWindow* ui;
        IViewer* _viewerAxl;
        IViewer* _viewerCor;
        IViewer* _viewerSag;
        void initConnection();
    private slots:
        void actionOpenDICOMTriggered();
        void actionOpenNIITriggered();
        void actionOpenDICOMSeriesTriggered();
};
#endif // MAINWINDOW_H

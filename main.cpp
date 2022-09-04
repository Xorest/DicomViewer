#include <QApplication>
#include <vtkAutoInit.h>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

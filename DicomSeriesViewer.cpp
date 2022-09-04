#include "DicomSeriesViewer.h"
#include <vtkDICOMImageReader.h>
#include <QDebug>

DicomSeriesViewer::DicomSeriesViewer(QVTKOpenGLNativeWidget* openGLwidget, QScrollBar* hScrollBar, QLabel* label)
    : IViewer(openGLwidget, hScrollBar, label)
{
}

void DicomSeriesViewer::setData(const QString& fileName)
{
    vtkNew<vtkDICOMImageReader> reader;
    reader->SetDirectoryName(fileName.toStdString().c_str());

    try
    {
        reader->Update();
    }
    catch (...)
    {
        qDebug() << "Nii File update error";
    }

    _imageViewer->SetInputConnection(reader->GetOutputPort());
}

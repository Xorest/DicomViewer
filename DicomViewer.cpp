#include <vtkDICOMImageReader.h>
#include <QDebug>
#include "DicomViewer.h"

DicomViewer::DicomViewer(QVTKOpenGLNativeWidget* openGLwidget, QScrollBar* hScrollBar, QLabel* label)
    : IViewer(openGLwidget, hScrollBar, label)
{
}

void DicomViewer::setData(const QString& fileName)
{
    vtkNew<vtkDICOMImageReader> reader;
    reader->SetFileName(fileName.toStdString().c_str());

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

#include <vtkNIFTIImageReader.h>
#include <vtkImageData.h>
#include "NiiViewer.h"
#include <QDebug>

NiiViewer::NiiViewer(QVTKOpenGLNativeWidget* openGLwidget, QScrollBar* hScrollBar, QLabel* label)
    : IViewer(openGLwidget, hScrollBar, label)
{
}

void NiiViewer::setData(const QString& fileName)
{
    vtkImageData* image = vtkImageData::New();
    vtkSmartPointer <vtkNIFTIImageReader> niiFile = vtkSmartPointer <vtkNIFTIImageReader>::New();
    niiFile->SetFileName(fileName.toStdString().c_str());

    try
    {
        niiFile->Update();
    }
    catch (...)
    {
        qDebug() << "Nii File update error";
    }

    image->DeepCopy(niiFile->GetOutput());
    _imageViewer->SetInputData(image);
}

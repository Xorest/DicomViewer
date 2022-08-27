#pragma once

//qt
#include <QtWidgets/QMainWindow>
#include <qstring.h>
#include <QVTKOpenGLStereoWidget.h>
#include "ui_mainwindow.h"
//vtk
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkImageData.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
//itk
#include <itkGDCMImageIO.h>
#include <itkGDCMSeriesFileNames.h>
#include <itkImageSeriesReader.h>
#include <itkImageToVTKImageFilter.h>

static const unsigned int InputDimension = 3;
typedef signed short PixelType;
typedef itk::Image<PixelType, InputDimension> InputImageType;
typedef itk::GDCMImageIO ImageIOType;
typedef itk::GDCMSeriesFileNames InputNamesGeneratorType;
typedef itk::ImageSeriesReader<InputImageType> ReaderType;
typedef itk::ImageToVTKImageFilter<InputImageType> ConnectorType;

class testQt : public QMainWindow
{
    Q_OBJECT

public:
    testQt(QWidget *parent = nullptr);
    ~testQt();

private:
    Ui::testQtClass ui;
    QString _folderNameDICOM;
    vtkSmartPointer<vtkImageViewer2> _viewerAxl, _viewerCor, _viewerSag;
    vtkImageData* _image;
    vtkCamera* _cam, * _activeCam;
    vtkSmartPointer<vtkRenderer> _renderer;
    ImageIOType::Pointer _gdcmIO;
    InputNamesGeneratorType::Pointer _inputNames;
    ReaderType::Pointer _reader;
    ConnectorType::Pointer _connector;
    int minSliceAxl, maxSliceAxl, minSliceCor, maxSliceCor, minSliceSag, maxSliceSag;
    void initVTKProcessRead();
    void initUI();
    void drawDICOMSeries(std::string folderDICOM);
    void showAxl();
    void showCor();
    void showSag();
private slots:
    void actionDICOMTriggered();
    void actionNIITriggered();
    void onHScrollBarAxlValueChanged(int value);
    void onHScrollBarCorValueChanged(int value);
    void onHScrollBarSagValueChanged(int value);
};

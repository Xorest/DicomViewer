#include "mainwindow.h"
#include <qdebug.h>
#include <qpushbutton.h>
#include <qfiledialog.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkWin32OpenGLRenderWindow.h>
#include <QVTKRenderWidget.h>

testQt::testQt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    initUI();
 
    _renderer = vtkSmartPointer<vtkRenderer>::New();
}

testQt::~testQt()
{}

void testQt::initVTKProcessRead() {
    //Initializaton
    _viewerAxl = vtkSmartPointer<vtkImageViewer2>::New();
    _viewerCor = vtkSmartPointer<vtkImageViewer2>::New();
    _viewerSag = vtkSmartPointer<vtkImageViewer2>::New();
    _gdcmIO = ImageIOType::New();
    _inputNames = InputNamesGeneratorType::New();
    _reader = ReaderType::New();
    _connector = ConnectorType::New();
    _image = vtkImageData::New();
    _activeCam = vtkCamera::New();
}

void testQt::initUI()
{
    connect(ui.actionOpenDICOM, &QAction::triggered, this, &testQt::actionDICOMTriggered);
    connect(ui.actionOpenNII, &QAction::triggered, this, &testQt::actionNIITriggered);
    connect(ui.hScrollBarAxl, &QScrollBar::valueChanged, this, &testQt::onHScrollBarAxlValueChanged);
    connect(ui.hScrollBarCor, &QScrollBar::valueChanged, this, &testQt::onHScrollBarCorValueChanged);
    connect(ui.hScrollBarSag, &QScrollBar::valueChanged, this, &testQt::onHScrollBarSagValueChanged);
}

void testQt::drawDICOMSeries(std::string folderDICOM)
{
    qDebug() << "LOG 0";
    //Read the input series
    _inputNames->SetInputDirectory(folderDICOM.c_str());
    const ReaderType::FileNamesContainer& filenames = _inputNames->GetInputFileNames();
    _reader->SetImageIO(_gdcmIO);
    _reader->SetFileNames(filenames);

    try 
    {
        _reader->Update();
    }
    catch (itk::ExceptionObject& excp) 
    {
        qDebug() << "Exception thrown while reading the series";
        qDebug() << excp.what();
    }

    //Connector to convert ITK image data to VTK image data
    _connector->SetInput(_reader->GetOutput()); //Set ITK reader Output to connector you can replace it with filter

    try 
    { //Exceptional handling
        _connector->Update();
    }
    catch (itk::ExceptionObject& e) 
    {
        qDebug() << "exception in file reader ";
        qDebug() << e.what();
    }
   
    _image->DeepCopy(_connector->GetOutput());

    showAxl();
    showCor();
    showSag();
}

void testQt::showAxl()
{
    _viewerAxl->SetRenderWindow(ui.qvtkopenGLWidgetAxl->renderWindow());
    _viewerAxl->SetInputData(_image);
    _viewerAxl->SetupInteractor(ui.qvtkopenGLWidgetAxl->renderWindow()->GetInteractor());
    //Flipping Y-axis (further checking needed)
    _cam = _viewerAxl->GetRenderer()->GetActiveCamera();
    _cam->SetPosition(0, 0, -1);
    _cam->SetViewUp(0, -1, 0);

    _viewerAxl->SetSliceOrientationToXY();

    // Gets the number of slices
    minSliceAxl = _viewerAxl->GetSliceMin();
    maxSliceAxl = _viewerAxl->GetSliceMax();
    _viewerAxl->SetSlice(_viewerAxl->GetSliceMax() / 2);
    _viewerAxl->GetRenderer()->ResetCamera();
    _viewerAxl->Render();
    ui.qvtkopenGLWidgetAxl->update();

    // Update GUI Labels
    ui.hScrollBarAxl->setMinimum(minSliceAxl);
    ui.hScrollBarAxl->setMaximum(maxSliceAxl);
    ui.hScrollBarAxl->setSliderPosition(maxSliceAxl / 2);
    ui.lblCurrentSliceAxl->setText("Slice: " + QString::number(_viewerAxl->GetSlice() + 1) + " of " + QString::number(maxSliceAxl + 1));

}

void testQt::showCor()
{
    //Set input image to VTK viewer
    _viewerCor->SetRenderWindow(ui.qvtkopenGLWidgetCor->renderWindow());
    _viewerCor->SetInputData(_image);
    _viewerCor->SetupInteractor(ui.qvtkopenGLWidgetCor->renderWindow()->GetInteractor());

    _viewerCor->SetSliceOrientationToXZ();

    // Gets the number of slices
    minSliceCor = _viewerCor->GetSliceMin();
    maxSliceCor = _viewerCor->GetSliceMax();
    _viewerCor->SetSlice(_viewerCor->GetSliceMax() / 2);
    _viewerCor->GetRenderer()->ResetCamera();
    _viewerCor->Render();
    ui.qvtkopenGLWidgetCor->update();

    // Update GUI Labels
    ui.hScrollBarCor->setMinimum(minSliceCor);
    ui.hScrollBarCor->setMaximum(maxSliceCor);
    ui.hScrollBarCor->setSliderPosition(maxSliceCor / 2);
    ui.lblCurrentSliceCor->setText("Slice: " + QString::number(_viewerCor->GetSlice() + 1) + " of " + QString::number(maxSliceCor + 1));

}

void testQt::showSag()
{
    //Set input image to VTK viewer
    _viewerSag->SetInputData(_image);

    _viewerSag->SetRenderWindow(ui.qvtkopenGLWidgetSag->renderWindow());
    _viewerSag->SetInputData(_image);
    _viewerSag->SetupInteractor(ui.qvtkopenGLWidgetSag->renderWindow()->GetInteractor());

    _viewerSag->SetSliceOrientationToYZ();

    // Gets the number of slices
    minSliceSag = _viewerSag->GetSliceMin();
    maxSliceSag = _viewerSag->GetSliceMax();
    _viewerSag->SetSlice(_viewerSag->GetSliceMax() / 2);
    _viewerSag->GetRenderer()->ResetCamera();
    _viewerSag->Render();
    ui.qvtkopenGLWidgetSag->update();

    // Update GUI Labels
    ui.hScrollBarSag->setMinimum(minSliceSag);
    ui.hScrollBarSag->setMaximum(maxSliceSag);
    ui.hScrollBarSag->setSliderPosition(maxSliceSag / 2);
    ui.lblCurrentSliceSag->setText("Slice: " + QString::number(_viewerSag->GetSlice() + 1) + " of " + QString::number(maxSliceSag + 1));

}

void testQt::actionDICOMTriggered()
{
    _folderNameDICOM = QFileDialog::getExistingDirectory(this, tr("Open DICOM Image/Folder"), "/", QFileDialog::ShowDirsOnly);
    if (!_folderNameDICOM.isEmpty()) {
        initVTKProcessRead();
        drawDICOMSeries(_folderNameDICOM.toUtf8().constData());
    }
}

void testQt::actionNIITriggered()
{

}

void testQt::onHScrollBarAxlValueChanged(int value)
{
    _viewerAxl->SetSlice(value);
    ui.lblCurrentSliceAxl->setText("Slice: " + QString::number(_viewerAxl->GetSlice() + 1) + " of " + QString::number(maxSliceAxl + 1));
    _viewerAxl->Render();
}

void testQt::onHScrollBarCorValueChanged(int value) {
    _viewerCor->SetSlice(value);
    ui.lblCurrentSliceCor->setText("Slice: " + QString::number(_viewerCor->GetSlice() + 1) + " of " + QString::number(maxSliceCor + 1));
    _viewerCor->Render();
}

void testQt::onHScrollBarSagValueChanged(int value) {
    _viewerSag->SetSlice(value);
    ui.lblCurrentSliceSag->setText("Slice: " + QString::number(_viewerSag->GetSlice() + 1) + " of " + QString::number(maxSliceSag + 1));
    _viewerSag->Render();
}
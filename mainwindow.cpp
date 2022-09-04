#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "NiiViewer.h"
#include "DicomSeriesViewer.h"
#include "DicomViewer.h"
#include <QVTKOpenGLNativeWidget.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initConnection()
{
    connect(ui->actionOpenDICOMSeries, &QAction::triggered, this, &MainWindow::actionOpenDICOMSeriesTriggered);
    connect(ui->actionOpenDICOM, &QAction::triggered, this, &MainWindow::actionOpenDICOMTriggered);
    connect(ui->actionOpenNII, &QAction::triggered, this, &MainWindow::actionOpenNIITriggered);
}

void MainWindow::actionOpenDICOMTriggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open .DCM"), QDir::currentPath(), tr("Image (*.dcm)"));

    if (!fileName.isEmpty())
    {
        _viewerAxl = new DicomViewer(ui->qvtkopenGLWidgetAxl, ui->hScrollBarAxl, ui->lblCurrentSliceAxl); //todo добавить менеджер который будет работать с widget
        _viewerAxl->draw(fileName);
        _viewerAxl->SetSliceOrientationToXY();

        _viewerCor = new DicomViewer(ui->qvtkopenGLWidgetCor, ui->hScrollBarCor, ui->lblCurrentSliceCor);
        _viewerCor->draw(fileName);
        _viewerCor->SetSliceOrientationToXZ();

        _viewerSag = new DicomViewer(ui->qvtkopenGLWidgetSag, ui->hScrollBarSag, ui->lblCurrentSliceSag);
        _viewerSag->draw(fileName);
        _viewerSag->SetSliceOrientationToYZ();
    }
}

void MainWindow::actionOpenNIITriggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open .NII"), QDir::currentPath(), tr("Image (*.nii)"));

    if (!fileName.isEmpty())
    {
        _viewerAxl = new NiiViewer(ui->qvtkopenGLWidgetAxl, ui->hScrollBarAxl, ui->lblCurrentSliceAxl); //todo добавить менеджер который будет работать с widget
        _viewerAxl->draw(fileName);
        _viewerAxl->SetSliceOrientationToXY();

        _viewerCor = new NiiViewer(ui->qvtkopenGLWidgetCor, ui->hScrollBarCor, ui->lblCurrentSliceCor);
        _viewerCor->draw(fileName);
        _viewerCor->SetSliceOrientationToXZ();

        _viewerSag = new NiiViewer(ui->qvtkopenGLWidgetSag, ui->hScrollBarSag, ui->lblCurrentSliceSag);
        _viewerSag->draw(fileName);
        _viewerSag->SetSliceOrientationToYZ();
    }
}

void MainWindow::actionOpenDICOMSeriesTriggered()
{
    QString folderName = QFileDialog::getExistingDirectory(this, tr("Open DICOM Image/Folder"), "/", QFileDialog::ShowDirsOnly);

    if (!folderName.isEmpty())
    {
        _viewerAxl = new DicomSeriesViewer(ui->qvtkopenGLWidgetAxl, ui->hScrollBarAxl, ui->lblCurrentSliceAxl); //todo добавить менеджер который будет работать с widget
        _viewerAxl->draw(folderName);
        _viewerAxl->SetSliceOrientationToXY();

        _viewerCor = new DicomSeriesViewer(ui->qvtkopenGLWidgetCor, ui->hScrollBarCor, ui->lblCurrentSliceCor);
        _viewerCor->draw(folderName);
        _viewerCor->SetSliceOrientationToXZ();

        _viewerSag = new DicomSeriesViewer(ui->qvtkopenGLWidgetSag, ui->hScrollBarSag, ui->lblCurrentSliceSag);
        _viewerSag->draw(folderName);
        _viewerSag->SetSliceOrientationToYZ();
    }
}


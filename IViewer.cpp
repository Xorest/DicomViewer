#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <QScrollBar>
#include "IViewer.h"

IViewer::IViewer(QVTKOpenGLNativeWidget* openGLwidget, QScrollBar* hScrollBar, QLabel* label)
    :_viewerWidget(new ViewerWidget(openGLwidget, hScrollBar, label)),
    minSlice(0),
    maxSlice(0)
{
    connect(hScrollBar, &QScrollBar::valueChanged, this, &IViewer::onHScrollBarValueChanged);
}

IViewer::~IViewer()
{
    disconnect(_viewerWidget->hScrollBar(), &QScrollBar::valueChanged, this, &IViewer::onHScrollBarValueChanged);
}

ViewerWidget* IViewer::viewerWidget() const
{
    return _viewerWidget;
}

void IViewer::draw(const QString& fileName)
{
    vtkNew<vtkNamedColors> colors;

    setData(fileName);

    vtkRenderWindow* renderWindow = _viewerWidget->renderWindow();
    _imageViewer->SetRenderWindow(renderWindow);
    _imageViewer->SetupInteractor(renderWindow->GetInteractor());
    _imageViewer->GetRenderer()->SetBackground(colors->GetColor3d("SlateGray").GetData());
    _imageViewer->Render();
    _viewerWidget->widget()->update();
    updateScrollBarAndLabel();
}

void IViewer::updateScrollBarAndLabel()
{
    minSlice = _imageViewer->GetSliceMin();
    maxSlice = _imageViewer->GetSliceMax();
    _imageViewer->SetSlice(maxSlice / 2);

    _imageViewer->GetRenderer()->ResetCamera();
    _imageViewer->Render();
    _viewerWidget->widget()->update();

    _viewerWidget->hScrollBar()->setMinimum(minSlice);
    _viewerWidget->hScrollBar()->setMaximum(maxSlice);
    _viewerWidget->hScrollBar()->setSliderPosition(maxSlice / 2);
    _viewerWidget->label()->setText("Slice: " + QString::number(_imageViewer->GetSlice() + 1) + " of " + QString::number(maxSlice + 1));
}

void IViewer::SetSliceOrientationToXY()
{
    _imageViewer->SetSliceOrientationToXY();
    updateScrollBarAndLabel();
}

void IViewer::SetSliceOrientationToXZ()
{
    _imageViewer->SetSliceOrientationToXZ();
    updateScrollBarAndLabel();
}

void IViewer::SetSliceOrientationToYZ()
{
    _imageViewer->SetSliceOrientationToYZ();
    updateScrollBarAndLabel();
}

void IViewer::onHScrollBarValueChanged(int value) 
{
    _imageViewer->SetSlice(value);
    _viewerWidget->label()->setText("Slice: " + QString::number(_imageViewer->GetSlice() + 1) + " of " + QString::number(maxSlice + 1));
    _imageViewer->Render();
}

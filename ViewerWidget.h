#pragma once
#include <qscrollbar.h>
#include <qlabel.h>
#include <vtkNew.h>
#include <vtkImageViewer2.h>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkSmartPointer.h>

class ViewerWidget
{
public:
	ViewerWidget(QVTKOpenGLNativeWidget* widget, QScrollBar* hScrollBar, QLabel* label) 
		: _widget(widget),
		_hScrollBar(hScrollBar),
		_label(label) 
	{
		_renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
		widget->setRenderWindow(_renderWindow);
	}

	QScrollBar* hScrollBar() { return _hScrollBar; }
	QLabel* label() { return _label; }
	QVTKOpenGLNativeWidget* widget() { return _widget; }
	vtkRenderWindow* renderWindow() { return _renderWindow; }
private:
	QScrollBar* _hScrollBar;
	QLabel* _label;
	QVTKOpenGLNativeWidget* _widget;
	vtkSmartPointer<vtkRenderWindow> _renderWindow;
};


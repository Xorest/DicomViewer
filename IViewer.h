#pragma once

#include "ViewerWidget.h"
#include <qobject.h>

class IViewer : public QObject
{
Q_OBJECT
public:
	IViewer(QVTKOpenGLNativeWidget* openGLwidget, QScrollBar* hScrollBar, QLabel* label);
	~IViewer();

    ViewerWidget* viewerWidget() const;
	void draw(const QString& fileName);
    void updateScrollBarAndLabel();
    void SetSliceOrientationToXY();
    void SetSliceOrientationToXZ();
    void SetSliceOrientationToYZ();
protected:
	void virtual setData(const QString& fileName) = 0;
     vtkNew<vtkImageViewer2> _imageViewer;
private:
    ViewerWidget* _viewerWidget;
	int minSlice, maxSlice;
private slots:
	void onHScrollBarValueChanged(int value);

};


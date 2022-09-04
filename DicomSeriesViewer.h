#pragma once
#include "IViewer.h"

class DicomSeriesViewer : public IViewer
{
public:
	DicomSeriesViewer(QVTKOpenGLNativeWidget* openGLwidget, QScrollBar* hScrollBar, QLabel* label);
protected:
	void setData(const QString& fileName) override;
};


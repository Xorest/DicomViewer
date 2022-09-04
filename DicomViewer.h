#pragma once
#include "IViewer.h"

class DicomViewer : public IViewer
{
public:
	DicomViewer(QVTKOpenGLNativeWidget* openGLwidget, QScrollBar* hScrollBar, QLabel* label);
protected:
	void setData(const QString& fileName) override;
};


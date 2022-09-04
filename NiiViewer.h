#pragma once
#include "IViewer.h"

class NiiViewer : public IViewer
{
public:
	NiiViewer(QVTKOpenGLNativeWidget* openGLwidget, QScrollBar* hScrollBar, QLabel* label);
protected:
	void setData(const QString& fileName) override;
};


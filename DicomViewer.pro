QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DicomSeriesViewer.cpp \
    DicomViewer.cpp \
    IViewer.cpp \
    NiiViewer.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    DicomSeriesViewer.h \
    DicomViewer.h \
    IViewer.h \
    NiiViewer.h \
    ViewerWidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

LIBS += -LD:/VTK_9.2.0/lib \
-lvtkCommonCore-9.2\
-lvtkCommonDataModel-9.2 \
-lvtkCommonExecutionModel-9.2 \
-lvtkGUISupportQt-9.2 \
-lvtkInteractionImage-9.2 \
-lvtkInteractionStyle-9.2 \
-lvtkIOImage-9.2 \
-lvtkRenderingCore-9.2 \
-lvtkRenderingFreeType-9.2 \
-lvtkRenderingOpenGL2-9.2 \
-lvtksys-9.2 \
-lvtkCommonColor-9.2

INCLUDEPATH += -L D:/VTK_9.2.0/include/vtk-9.2

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

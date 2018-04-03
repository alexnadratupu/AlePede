#-------------------------------------------------
#
# Project created by QtCreator 2018-03-18T22:05:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PedestrianDetection3
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    maincontroller.cpp \
    image.cpp \
    histogram.cpp \
    basic.cpp \
    filter.cpp \
    imagenpgm.cpp \
    edgedetector.cpp \
    segmentation.cpp \
    imagenppm.cpp \
    imagefile.cpp \
    cannywidget.cpp \
    changeframewidget.cpp \
    colordepthqwidget.cpp \
    convolutionqwidget.cpp \
    sobelqwidget.cpp \
    structureelementqwidget.cpp \
    thresholdqwidget.cpp \
    windowlevelqwidget.cpp \
    customqlabel.cpp

HEADERS += \
        mainwindow.h \
    maincontroller.h \
    image.h \
    histogram.h \
    basic.h \
    filter.h \
    imagenpgm.h \
    edgedetector.h \
    segmentation.h \
    imagenppm.h \
    imagefile.h \
    cannywidget.h \
    changeframewidget.h \
    colordepthqwidget.h \
    convolutionqwidget.h \
    sobelqwidget.h \
    structureelementqwidget.h \
    thresholdqwidget.h \
    windowlevelqwidget.h \
    customqlabel.h

FORMS += \
        mainwindow.ui \
    cannywidget.ui \
    changeframewidget.ui \
    colordepthqwidget.ui \
    convolutionqwidget.ui \
    sobelqwidget.ui \
    structureelementqwidget.ui \
    thresholdqwidget.ui \
    windowlevelqwidget.ui \
    customqlabel.ui

INCLUDEPATH += D:\openCv\opencv\release\install\include

LIBS += D:\openCv\opencv\release\bin\libopencv_core320.dll
LIBS += D:\openCv\opencv\release\bin\libopencv_highgui320.dll
LIBS += D:\openCv\opencv\release\bin\libopencv_imgcodecs320.dll
LIBS += D:\openCv\opencv\release\bin\libopencv_imgproc320.dll
LIBS += D:\openCv\opencv\release\bin\libopencv_calib3d320.dll



#-------------------------------------------------
#
# Project created by QtCreator 2016-03-20T14:10:55
#
#-------------------------------------------------

QT       += core gui opengl printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = robotSimulator
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    harness.cpp \
    inversekinematicsengine.cpp \
    trajectoryinterpolator.cpp \
    robotmodel.cpp \
    robotvisualisationwidget.cpp \
    machinecoordinatesplot.cpp \
    point.cpp \
    machinecoordinates.cpp \
    gui.cpp \
    pointdialog.cpp \
    settingsdialog.cpp \
    defaultvalues.cpp \
    timeplotwidget.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    harness.h \
    inversekinematicsengine.h \
    trajectoryinterpolator.h \
    robotmodel.h \
    robotvisualisationwidget.h \
    machinecoordinatesplot.h \
    machineparameters.h \
    approachvector.h \
    deltas.h \
    machinecoordinates.h \
    point.h \
    gui.h \
    pointdialog.h \
    kinematicsmode.h \
    settingsdialog.h \
    defaultvalues.h \
    timeplotwidget.h \
    qcustomplot.h

DEPENDPATH += C:\Qt\5.6\mingw49_32\bin

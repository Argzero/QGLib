#-------------------------------------------------
#
# Project created by QtCreator 2016-01-07T03:33:54
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QGLExample
TEMPLATE = app

SOURCES  += main.cpp\
            mainwindow.cpp \
            RLI_QGL/global.cpp \
            RLI_QGL/qglwindow.cpp \
            RLI_QGL/geometry/line.cpp \
            RLI_QGL/geometry/plane.cpp \
            RLI_QGL/geometry/vector2.cpp \
            RLI_QGL/geometry/vector3.cpp \
            RLI_QGL/geometry/quaternion.cpp \
            RLI_QGL/objects/qglobject.cpp \
            RLI_QGL/objects/special/iclickable.cpp \
            RLI_QGL/objects/text/qgltext.cpp \
            RLI_QGL/objects/scenes/scenenode.cpp \
            RLI_QGL/utils/qglmath.cpp

HEADERS  += mainwindow.h \
            RLI_QGL/qglwindow.h \
            RLI_QGL/geometry/line.h \
            RLI_QGL/geometry/plane.h \
            RLI_QGL/geometry/vector2.h \
            RLI_QGL/geometry/vector3.h  \
            RLI_QGL/geometry/quaternion.h \
            RLI_QGL/objects/qglobject.h \
            RLI_QGL/objects/special/iclickable.h \
            RLI_QGL/objects/text/qgltext.h \
            RLI_QGL/objects/scenes/scenenode.h \
            RLI_QGL/utils/qglconstants.hpp \
            RLI_QGL/utils/qglmath.h
FORMS               += mainwindow.ui
LIBS                += -framework QtGui -framework QtOpenGL -framework QtCore -framework OpenGL -lm -ldl # -lGL -lGLU
INCLUDEPATH         += $$PWD/RLI_QGL
DEPENDPATH          += $$PWD/RLI_QGL
RESOURCES           += \
    RLI_QGL.qrc
CONFIG              += console

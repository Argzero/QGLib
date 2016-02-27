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
            RLI_QGL/qglwindow.cpp \
            RLI_QGL/vector2.cpp \
            RLI_QGL/vector3.cpp \
            RLI_QGL/utils/qglmath.cpp \
            RLI_QGL/objects/qglobject.cpp \
            RLI_QGL/objects/text/qgltext.cpp \
            RLI_QGL/objects/shapes/qglshape.cpp \
            RLI_QGL/objects/shapes/triangles/qgltriangle.cpp \
            RLI_QGL/objects/shapes/quads/qglquad.cpp \
            RLI_QGL/objects/shapes/polygons/qglpolygon.cpp \
            RLI_QGL/scenes/scenenode.cpp

HEADERS  += mainwindow.h \
            RLI_QGL/qglwindow.h \
            RLI_QGL/qglconstants.hpp \
            RLI_QGL/vector2.h \
            RLI_QGL/vector3.h \
            RLI_QGL/utils/qglmath.h \
            RLI_QGL/objects/qglobject.h \
            RLI_QGL/objects/text/qgltext.h \
            RLI_QGL/objects/shapes/qglshape.h \
            RLI_QGL/objects/shapes/triangles/qgltriangle.h \
            RLI_QGL/objects/shapes/quads/qglquad.h \
            RLI_QGL/objects/shapes/polygons/qglpolygon.h \
            RLI_QGL/scenes/scenenode.h

FORMS    += mainwindow.ui

LIBS     += -lGL -lGLU
INCLUDEPATH += $$PWD/RLI_QGL
DEPENDPATH += $$PWD/RLI_QGL
RESOURCES += RLI_QGL.qrc

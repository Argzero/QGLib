#include <QGLWidget>
#include <QFontDatabase>
#include <QPainter>
#include <QTimer>
#ifndef QGLWINDOW_H
#define QGLWINDOW_H

#include <string>

#include "objects/qglobject.h"
#include "objects/text/qgltext.h"
#include "objects/shapes/qglshape.h"
#include "objects/shapes/quads/qglquad.h"
#include "objects/shapes/triangles/qgltriangle.h"
#include "objects/shapes/polygons/qglpolygon.h"
#include "vector3.h"

class QGLWindow : public QGLWidget
{
    Q_OBJECT
public:
    explicit QGLWindow(QWidget *parent = 0);
    virtual ~QGLWindow();
    QTimer *updateTimer;

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    // Convenience Functions
    void qglColor(QColor color);
    void qglClearColor(QColor clearColor);
    void addBg(QVector<QColor> c);
    void clear(QPainter *p);
    void start();

    void updateCursor();

    virtual void addComponents();

    // Add Objects to Scene
    QGLText* AddText(QGLObject *_parent, Vector3 _pos, string _text = "", int _size = 18, QColor _color = Qt::red, QGLObject::ALIGN _align = QGLObject::CENTER_MID);

    // Triangle
    QGLTriangle* AddTriangle(QGLObject *_parent, Vector3 _pos,
                             QVector<Vector3> *_corners, QColor _color,
                             bool _wireframe = false, QColor _frameColor = Qt::black);
    QGLTriangle* AddTriangle(QGLObject *_parent, Vector3 _pos,
                             QVector<Vector3> *_corners, QVector<QColor> *_colors,
                             bool _wireframe = false, QColor _frameColor = Qt::black);
    //Equilateral Triangle
    QGLTriangle* AddTriangle(QGLObject *_parent, Vector3 _pos,
                             float _radius, float _rotation = 0.0, QColor _color = Qt::black,
                             bool _wireframe = false, QColor _frameColor = Qt::black);
    QGLTriangle* AddTriangle(QGLObject *_parent, Vector3 _pos,
                             float _radius, float _rotation, QVector<QColor> *_colors,
                             bool _wireframe = false, QColor _frameColor = Qt::black);
    // Quadritlaterals
    QGLQuad* AddQuad(QGLObject *_parent, Vector3 _pos,
                     QVector<Vector3> *_vertices, QColor _color,
                     bool _wireframe= false, QColor _frameColor=Qt::black,
                     QGLQuad::RENDER_TYPE _renderType = QGLQuad::TWO_TRIANGLES,
                     QGLQuad::FRAME_TYPE _frameType = QGLQuad::FULL_FRAME);
    QGLQuad* AddQuad(QGLObject *_parent, Vector3 _pos,
                     QVector<Vector3> *_vertices, QVector<QColor> *_colors,
                     bool _wireframe= false, QColor _frameColor=Qt::black,
                     QGLQuad::RENDER_TYPE _renderType = QGLQuad::TWO_TRIANGLES,
                     QGLQuad::FRAME_TYPE _frameType = QGLQuad::FULL_FRAME);

    void bgOff();
    void bgOn();

    //.........OBJECTS..........//
    QVector<QGLObject*> *objects;
    Vector2 mouse;
    QVector<QColor> bgRectColors; //0-3 top-left, clockwise; 4 center.
    Vector2 bgCenterOffset;

private:
    bool bgON;

signals:

public slots:

};
#endif // QGLWINDOW_H

#ifndef QGLTRIANGLE_H
#define QGLTRIANGLE_H

#include <QtMath>

#include "../qglshape.h"
#include "../../../vector3.h"

///////////////////////////////////////////////////////////////
/// NOTES:
///     - TRIANGLES ARE _UNLIT_ UNLESS YOU TELL THEM TO BE LIT!
///     - Can be instantiated equilateral; also has a generic triangle constructor
///////////////////////////////////////////////////////////////


class QGLTriangle  : public QGLShape
{
public:
    // CONSTRUCTORS
    QGLTriangle();
    // EQUILATERAL TRIANGLE
    QGLTriangle(QGLObject *_parent, Vector3 _pos,
                float _radius, QColor _color, float _rotation = 0.0 /*degrees*/,
                bool _wireframe= false, QColor _frameColor=Qt::black);
    QGLTriangle(QGLObject *_parent, Vector3 _pos,
                float _radius, QVector<QColor> *_colors, float _rotation = 0.0 /*degrees*/,
                bool _wireframe= false, QColor _frameColor=Qt::black);
    // ANY TYPE OF TRIANGLE
    QGLTriangle(QGLObject *_parent, Vector3 _pos,
                QVector<Vector3> *_corners, QColor _color,
                bool _wireframe= false, QColor _frameColor=Qt::black);
    QGLTriangle(QGLObject *_parent, Vector3 _pos,
                QVector<Vector3> *_corners, QVector<QColor> *_colors,
                bool _wireframe= false, QColor _frameColor=Qt::black);
    ~QGLTriangle();

    // Functions
    virtual void update();
    virtual void draw(QPainter *p);
    virtual Vector3 GetCenter();
    virtual void contains(Vector2 point);
};

#endif // QGLRECT_H

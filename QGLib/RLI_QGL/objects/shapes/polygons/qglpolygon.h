#ifndef QGLPOLYGON_H
#define QGLPOLYGON_H
#include "../qglshape.h"
#include "../../../vector3.h"

class QGLPolygon : public QGLShape
{
public:
    // 4 vertices for TWO_TRIANGLES, 5 for FOUR_TRIANGLES
    QGLPolygon();
    QGLPolygon(QGLObject *_parent, Vector3 _pos,
            QVector<Vector3> *_vertices, QColor _color,
            bool _wireframe= false, QColor _frameColor=Qt::black,
            FRAME_TYPE _frameType = FULL_FRAME);
    QGLPolygon(QGLObject *_parent, Vector3 _pos,
            QVector<Vector3> *_vertices, QVector<QColor> *_colors,
            bool _wireframe= false, QColor _frameColor=Qt::black,
            FRAME_TYPE _frameType = FULL_FRAME);
    ~QGLPolygon();

    // Functions
    virtual void update();
    virtual void draw(QPainter *p);
    virtual void contains(Vector2 point);
    virtual Vector3 GetCenter();

    // Variables
protected:
    QGLObject::FRAME_TYPE frameType;
    Vector3 centerPoint;
    bool lit;
};
#endif // QGLPOLYGON_H

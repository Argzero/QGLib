#ifndef QGLQUAD_H
#define QGLQUAD_H

#include "../qglshape.h"
#include "../../../vector3.h"

class QGLQuad : public QGLShape
{
public:
    typedef enum
    {
        TWO_TRIANGLES,
        FOUR_TRIANGLES
    } RENDER_TYPE; // Divisions of the quad

    typedef enum
    {
        INNER_ONLY,
        OUTER_ONLY,
        FULL_FRAME
    } FRAME_TYPE; // Outlines of the quad divisions

    // 4 vertices for TWO_TRIANGLES, 5 for FOUR_TRIANGLES
    QGLQuad();
    QGLQuad(QGLObject *_parent, Vector3 _pos,
            QVector<Vector3> *_vertices, QColor _color,
            bool _wireframe= false, QColor _frameColor=Qt::black,
            RENDER_TYPE _renderType = TWO_TRIANGLES,
            FRAME_TYPE _frameType = FULL_FRAME);
    QGLQuad(QGLObject *_parent, Vector3 _pos,
            QVector<Vector3> *_vertices, QVector<QColor> *_colors,
            bool _wireframe= false, QColor _frameColor=Qt::black,
            RENDER_TYPE _renderType = TWO_TRIANGLES,
            FRAME_TYPE _frameType = FULL_FRAME);
    ~QGLQuad();

    // Functions
    virtual void update();
    virtual void draw(QPainter *p);
    virtual void contains(Vector2 point);
    virtual Vector3 GetCenter();

    // Variables
protected:
    RENDER_TYPE renderType;
    FRAME_TYPE frameType;
    Vector3 centerPoint;
    bool lit;
};
#endif // QGLQUAD_H

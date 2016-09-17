#ifndef QGLQUAD_H
#define QGLQUAD_H

#include "../qglshape.h"
#include "../../../geometry/vector3.h"

class QGLObject;
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
            bool _mouseEnable = false, bool _wireframe = false,
            QColor _frameColor = Qt::black,
            RENDER_TYPE _renderType = TWO_TRIANGLES,
            FRAME_TYPE _frameType = FULL_FRAME);
    QGLQuad(QGLObject *_parent, Vector3 _pos,
            QVector<Vector3> *_vertices, QVector<QColor> *_colors,
            bool _mouseEnable = false, bool _wireframe = false,
            QColor _frameColor = Qt::black,
            RENDER_TYPE _renderType = TWO_TRIANGLES,
            FRAME_TYPE _frameType = FULL_FRAME);
    ~QGLQuad();

    // Functions
    virtual void Update();
    virtual void Draw(QPainter *p);
    virtual Vector3 GetCenter();
    //MOUSE
    virtual bool CheckClicked();
    virtual bool CheckMouseOver(QPainter*);

    // Variables
protected:
    RENDER_TYPE renderType;
    FRAME_TYPE frameType;
    Vector3 centerPoint;
    bool lit;
};
#endif // QGLQUAD_H

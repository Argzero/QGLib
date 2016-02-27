#ifndef QGLSHAPE_H
#define QGLSHAPE_H

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include "../qglobject.h"

class QGLShape : public QGLObject
{
public:
    // SHAPE types
    typedef enum
    {
        BLANK,
        TRIANGLE,
        CIRCLE,
        QUAD,
        POLYGON // n-gon
    } SHAPE;

    // Constructors
    QGLShape();
    QGLShape(QGLObject *_parent, Vector3 _pos,
             ALIGN _align, bool _wireframe,
             QColor _frameColor);
    virtual ~QGLShape();

    // Functions
    virtual void update();
    virtual void draw(QPainter *p);
    virtual void contains(Vector2 point)=0;
    virtual Vector3 GetCenter()=0;

    // Variables
    QVector<Vector3> *vertices;
    QVector<QColor> *colors;
    QColor frameColor;

    bool wireframe;
    bool fill;
    bool lit;

    float wireframeThickness;

    ALIGN alignment;
    SHAPE shape;
    // GLenum renderType;
//protected:
    // QVector<QGLShape*> *parts;
};
#endif // QGLSHAPE_H

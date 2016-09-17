#ifndef QGLSHAPE_H
#define QGLSHAPE_H

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include "../qglobject.h"
#include "../special/iclickable.h"

class QGLShape : public QGLObject, public IClickable
{
public:
    // SHAPE types
    typedef enum
    {
        BLANK,
        TRIANGLE,
        CIRCLE,
        QUAD,
        SURFACE // n-gon
    } SHAPE;

    // Constructors
    QGLShape();
    QGLShape(QGLObject *_parent, Vector3 _pos, bool _mouseEnable,
             ALIGN _align, bool _wireframe,
             QColor _frameColor);
    virtual ~QGLShape();

    // Functions
    virtual void Update();
    virtual void Draw(QPainter *p);
    virtual Vector3 GetCenter() = 0;
    //MOUSE
    virtual bool CheckClicked() = 0;
    virtual bool CheckMouseOver(QPainter*) = 0;

    // Variables
    QVector<Vector3> *vertices;
    QVector<QColor> *colors;
    QColor frameColor;

    bool wireframe;
    bool fill;
    bool lit;

    float wireframeThickness;
    bool mouseEnabled;
    ALIGN alignment;
    SHAPE shape;
    // GLenum renderType;
//protected:
    // QVector<QGLShape*> *parts;
};
#endif // QGLSHAPE_H

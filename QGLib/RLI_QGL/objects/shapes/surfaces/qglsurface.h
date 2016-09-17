#ifndef QGLSurface_H
#define QGLSurface_H
#include "../qglshape.h"
#include "../../../geometry/vector3.h"

class QGLObject;
class QGLSurface : public QGLShape
{
public:
    QGLSurface();
    QGLSurface(QGLObject *_parent, Vector3 _pos,
            QVector<Vector3> *_vertices, QColor _color,
            bool _mouseEnable = false,
            bool _wireframe = false, QColor _frameColor = Qt::black);
    QGLSurface(QGLObject *_parent, Vector3 _pos,
            QVector<Vector3> *_vertices, QVector<QColor> *_colors,
            bool _mouseEnable = false,
            bool _wireframe = false, QColor _frameColor = Qt::black);
    ~QGLSurface();

    // Functions
    virtual void Update();
    virtual void Draw(QPainter *p);
    virtual Vector3 GetCenter();
    //MOUSE
    virtual bool CheckClicked();
    virtual bool CheckMouseOver(QPainter*);

    // Variables
protected:
//  QGLObject::FRAME_TYPE frameType;
    Vector3 centerPoint;
    bool lit;
};
#endif // QGLSurface_H

#ifndef QGLOBJECT_H
#define QGLOBJECT_H

#include <QVector>
#include <QPainter>
#include <QGLWidget>

#include "../vector3.h"
#include "../vector2.h"

class QGLObject
{
public:
    typedef enum
    {
        EMPTY,
        TEXT,
        SHAPE,
        MODEL
    } TYPE;

    // Alignment
    typedef enum
    {
        CENTER_TOP,
        CENTER_MID,
        CENTER_BOTTOM,
        LEFT_TOP,
        LEFT_MID,
        LEFT_BOTTOM,
        RIGHT_TOP,
        RIGHT_MID,
        RIGHT_BOTTOM
    } ALIGN;

    typedef enum
    {
        INNER_ONLY,
        OUTER_ONLY,
        FULL_FRAME
    } FRAME_TYPE; // Outlines of the polygon divisions

    QGLObject(QGLObject::TYPE _type = EMPTY, QGLObject *_parent = NULL,
              Vector3 _pos = Vector3::Zero, QGLObject::ALIGN _align = QGLObject::CENTER_MID);
    virtual ~QGLObject();

    virtual void update();
    virtual void draw(QPainter *p);
    Vector3 GetPosition();
    virtual void contains(Vector2 point)=0;

    QGLWidget *window;
    QGLObject *parent;

    QVector<QGLObject*> *children;
    TYPE type;
    ALIGN alignment;
    int id;
    static int countCreated;
protected:
    Vector3 position;
};

/*************************************************************************
 * Additional functionality for all new QGLObjects should be added
 * directly to those objects.
 *
 * If update and draw are undefined in subclasses they will do nothing.
 **************************************************************************/
#endif // QGLOBJECT_H

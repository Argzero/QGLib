#ifndef QGLOBJECT_H
#define QGLOBJECT_H

#include <QVector>
#include <QPainter>
#include <QOpenGLWidget>
#include "../geometry/vector3.h"
#include "../geometry/vector2.h"
class QGLObject
{
public:
    typedef enum
    {
        EMPTY,
        TEXT,
        SHAPE,
        SCENE
    } TYPE;

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

    typedef enum
    {
        RELATIVE,
        ABSOLUTE
    } POSITIONING;

    QGLObject(QGLObject::TYPE _type = EMPTY, QGLObject *_parent = NULL,
              Vector3 _pos = Vector3::Zero, Vector3 _rot = Vector3(1,1,1),
              Vector3 _scale = Vector3(1,1,1), QGLObject::ALIGN _align = QGLObject::CENTER_MID,
              /*TODO: Implement in subclasses*/
              QGLObject::POSITIONING _posType = QGLObject::ABSOLUTE);
    virtual ~QGLObject();

    // Object State Change and Display
    virtual void Update();
    virtual void Draw(QPainter *p);

    // Object State Calculation
    Vector3 GetPosition();
    Vector3 GetScale();
    Vector3 GetRotation();

    // Object References
    QOpenGLWidget *window;
    QGLObject *parent;
    QVector<QGLObject*> children;

    // Object Attributes
    TYPE type;
    ALIGN alignment;
    POSITIONING positioning;
    Vector3 rotation;
    Vector3 scale;

    // Identification and Configuration
    int id;
    bool enabled;
    static int countCreated;

    // Adding Child Objects
    void AddChild(QGLObject* _child);

protected:
    Vector3 position;
};

/*************************************************************************
 * Additional functionality for all new QGLObjects should be added
 * directly to those objects.
 **************************************************************************/

#endif // QGLOBJECT_H

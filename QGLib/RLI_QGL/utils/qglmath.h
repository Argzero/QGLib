#ifndef QGLMATH_H
#define QGLMATH_H

#include <QGLWidget>

#include "../vector3.h"
#include "../vector2.h"

class QGLMath
{
public:
    // Matrix and GLMath
    static GLint project(GLdouble objx, GLdouble objy, GLdouble objz,
                        const GLdouble model[16], const GLdouble proj[16],
                        const GLint viewport[4],
                        GLdouble *winx, GLdouble *winy, GLdouble *winz);
    static void transformPoint(GLdouble out[4], const GLdouble m[16], const GLdouble in[4]);

    // Tricks and Tools
    static float fMap(float,float,float,float,float);
    static float fLockedMap(float,float,float,float,float);

    // Average of Vector objects
    static Vector3 AvgVector3(QVector<Vector3> pts);
    static Vector2 AvgVector2(QVector<Vector2> pts);
};

#endif // QGLMATH_H

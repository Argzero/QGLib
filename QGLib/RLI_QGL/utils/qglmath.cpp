#include "qglmath.h"

#include "../vector3.h"
#include "../vector2.h"

// Average of Vector3 objects
Vector3 QGLMath::AvgVector3(QVector<Vector3> pts)
{
    int count = pts.length();
    Vector3 avg;
    while(pts.length()>0){
        avg += pts.takeFirst();
    }
    return avg/count;
}

// Average of Vector2 objects
Vector2 QGLMath::AvgVector2(QVector<Vector2> pts)
{
    int count = pts.length();
    Vector2 avg;
    while(pts.length()>0){
        avg += pts.takeFirst();
    }
    return avg/count;
}

// utility: float map
float QGLMath::fMap(float in, float min_a, float max_a, float min_b, float max_b)
{
    return (((in-min_a)/(max_a-min_a))*(max_b-min_b))+min_b;
}

// locks values in a range
float QGLMath::fLockedMap(float in, float min_a, float max_a, float min_b, float max_b)
{
    if(in < min_a)
        in = min_a;
    if(in > max_a)
        in = max_a;
    return fMap(in, min_a, max_a, min_b, max_b);
}

void QGLMath::transformPoint(GLdouble out[4], const GLdouble m[16], const GLdouble in[4])
{
#define M(row,col)  m[col*4+row]
    out[0] =
        M(0, 0) * in[0] + M(0, 1) * in[1] + M(0, 2) * in[2] + M(0, 3) * in[3];
    out[1] =
        M(1, 0) * in[0] + M(1, 1) * in[1] + M(1, 2) * in[2] + M(1, 3) * in[3];
    out[2] =
        M(2, 0) * in[0] + M(2, 1) * in[1] + M(2, 2) * in[2] + M(2, 3) * in[3];
    out[3] =
        M(3, 0) * in[0] + M(3, 1) * in[1] + M(3, 2) * in[2] + M(3, 3) * in[3];
#undef M
}

GLint QGLMath::project(GLdouble objx, GLdouble objy, GLdouble objz,
    const GLdouble model[16], const GLdouble proj[16],
    const GLint viewport[4],
    GLdouble *winx, GLdouble *winy, GLdouble *winz)
{
    GLdouble in[4], out[4];

    in[0] = objx;
    in[1] = objy;
    in[2] = objz;
    in[3] = 1.0;
    transformPoint(out, model, in);
    transformPoint(in, proj, out);

    if (in[3] == 0.0)
        return GL_FALSE;

    in[0] /= in[3];
    in[1] /= in[3];
    in[2] /= in[3];

    *winx = viewport[0] + (1 + in[0]) * viewport[2] / 2;
    *winy = viewport[1] + (1 + in[1]) * viewport[3] / 2;

    *winz = (1 + in[2]) / 2;
    return GL_TRUE;
}

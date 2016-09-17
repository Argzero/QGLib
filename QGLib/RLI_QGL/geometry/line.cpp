// CONDITIONALS FOR OS-SPECIFIC FUNCTIONALITY
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include <limits>
#include "line.h"
#include "vector3.h"

Line::Line(Vector3 a, Vector3 b)
{
    point = a;
    slope = (b-a).normalized();
}

Vector3 Line::projectToPlane(Plane p)
{
    using namespace std;
    if(slope.dot(p.normal)==0)
        return Vector3(numeric_limits<float>::infinity(),
                       numeric_limits<float>::infinity(),
                       numeric_limits<float>::infinity());
    float t = -((point.dot(p.normal)+p.d)/(slope.dot(p.normal)));
    return Vector3(point.X + t*(slope.X),
                   point.Y + t*(slope.Y),
                   point.Z + t*(slope.Z));
}

float Line::length()
{
    return slope.mag();
}

void Line::Draw(QPainter *p)
{
    p->beginNativePainting();
        glLineWidth(2.5f);
        glBegin(GL_LINE_STRIP); // TODO: Transparency
            glColor3f(255.0f/255.0f, 215.0f/255.0f, 0.0f);
            glVertex3f(point.X, point.Y, point.Z);

            glColor3f(255.0f/255.0f, 215.0f/255.0f, 0.0f);
            glVertex3f((point+slope).X, (point+slope).Y, (point+slope).Z);
        glEnd();

        /*
        int w = 50;
        glBegin(GL_TRIANGLES); // TODO: Transparency
            glColor3f(150.0f/255.0f, 215.0f/255.0f, 150.0f);
            glVertex3f((point+slope).X-w/2, (point+slope).Y+w/2, (point+slope).Z);
            glVertex3f((point+slope).X+w/2, (point+slope).Y+w/2, (point+slope).Z);
            glVertex3f((point+slope).X, (point+slope).Y-w/2, (point+slope).Z);
        glEnd();*/
        glLineWidth(1.0f);
    p->endNativePainting();
}

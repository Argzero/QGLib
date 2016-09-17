#ifndef LINE_H
#define LINE_H

#include <QPainter>

#include "vector3.h"
#include "plane.h"

struct Line
{
public:
    Vector3 point, slope;
    Line(Vector3, Vector3);

    Vector3 projectToPlane(Plane p);
    float length();
    void Draw(QPainter* p);
};

#endif // LINE_H

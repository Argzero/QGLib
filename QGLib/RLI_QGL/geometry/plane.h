#ifndef PLANE_H
#define PLANE_H

#include "vector3.h"

struct Plane
{
public:
    Vector3 normal, point;
    float d;

    // points of a triangle, p-q-r
    Plane(Vector3 p, Vector3 q, Vector3 r);
    void printEqn();
};

#endif // PLANE_H

#ifndef QUATERNION_H
#define QUATERNION_H

#include <QtMath>

struct Quaternion
{
public:
    float X;
    float Y;
    float Z;
    float W;

    // Constructors
    Quaternion() : X(0), Y(0), Z(0), W(1){}
    Quaternion(float _x, float _y, float _z, float _w): X(_x), Y(_y), Z(_z), W(_w){}

    // Special Case
    static Quaternion Identity;
    QString ToString();
};

#endif // QUATERNION_H

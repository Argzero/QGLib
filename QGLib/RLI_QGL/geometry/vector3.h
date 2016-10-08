#ifndef VECTOR3_H
#define VECTOR3_H

#include <QtMath>

#include "quaternion.h"

struct Vector3
{
public:
    float X;
    float Y;
    float Z;

    // Constructors
    Vector3() : X(0), Y(0), Z(0){}
    Vector3(float _x, float _y, float _z): X(_x), Y(_y), Z(_z){}

    // Functions
    Vector3 normalized();
    Vector3 rotate(const Vector3& angle);
    Vector3 cross(const Vector3);
    float dot(const Vector3);
    float mag();

    // Operators
    Vector3 operator +(const Vector3& other);
    Vector3 operator -(const Vector3& other);
    friend Vector3 operator *(Vector3, const float& other);
    friend Vector3 operator /(Vector3, const float& other);

    Vector3& operator +=(const Vector3& other);
    Vector3& operator -=(const Vector3& other);
    Vector3& operator *=(const float& other);
    Vector3& operator /=(const float& other);

    // Special Case
    static Vector3 Zero;
    QString ToString();
};

#endif // VECTOR3_H

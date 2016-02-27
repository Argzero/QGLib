#ifndef VECTOR2_H
#define VECTOR2_H

#include <QtMath>

struct Vector2
{
public:
    float X;
    float Y;

    // Constructors
    Vector2() : X(0), Y(0){};
    Vector2(float _x, float _y): X(_x), Y(_y){};

    // Functions
    Vector2 normalized();
    float mag();

    // Operators
    Vector2 operator +(const Vector2& other);
    friend Vector2 operator -(const Vector2& other);
    friend Vector2 operator *(Vector2, const float& other);
    friend Vector2 operator /(Vector2, const float& other);

    Vector2& operator +=(const Vector2& other);
    Vector2& operator -=(const Vector2& other);
    Vector2& operator *=(const float& other);
    Vector2& operator /=(const float& other);

    // Special Case
    static Vector2 Zero;
};

#endif // VECTOR2_H


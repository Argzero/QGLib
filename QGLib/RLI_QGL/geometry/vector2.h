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
    Vector2 rotate(const float& angle);
    Vector2 cross(Vector2);
    float dot(Vector2);
    float angleTo(Vector2);
    float angleFrom(Vector2);
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
    QString ToString();
};

#endif // VECTOR2_H


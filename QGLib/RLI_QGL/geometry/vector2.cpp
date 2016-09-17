#include "vector2.h"
#define VALUE (*this)

// Vector with a Mag of 1
Vector2 Vector2::normalized()
{
   return VALUE / mag();
}

// Magnitude of Vector
float Vector2::mag()
{
    return qSqrt(qPow(X,2)
                + qPow(Y,2));
}

// Addition Operators
Vector2 Vector2::operator +(const Vector2& other)
{
    return Vector2(this->X + other.X,
                   this->Y + other.Y);
}
Vector2& Vector2::operator +=(const Vector2& other)
{
    VALUE = Vector2(this->X + other.X,
                    this->Y + other.Y);
    return VALUE;
}

// Subtraction Operators
Vector2 operator -(const Vector2 self, const Vector2& other)
{
    return Vector2(self.X - other.X,
                   self.Y - other.Y);
}
Vector2& Vector2::operator -=(const Vector2& other)
{                                                         // but often is, to modify the private members)
    VALUE = Vector2(this->X - other.X,
                    this->Y - other.Y);
    return VALUE;
}

// Multiplication Operators
Vector2 operator *(const Vector2 self, const float& other)
{
    return Vector2(self.X * other,
                   self.Y * other);
}
Vector2& Vector2::operator *=(const float& other)
{
    VALUE = Vector2(this->X * other,
                    this->Y * other);
    return VALUE;
}

// Division Operators
Vector2 operator /(const Vector2 self, const float& other)
{
    return Vector2(self.X / other,
                   self.Y / other);
}
Vector2& Vector2::operator /=(const float& other)
{
    VALUE = Vector2(this->X / other,
                    this->Y / other);
    return VALUE;
}

// Vector 3DMath
float Vector2::dot(Vector2 b)
{
    return this->X*b.X + this->Y*b.Y;
}

Vector2 Vector2::cross(Vector2 b)
{
    return Vector2(this->X*b.Y, this->Y*b.X);
}

float Vector2::angleTo(Vector2 b)
{
    return this->dot(b)/(b.mag() * this->mag());
}

float Vector2::angleFrom(Vector2 b)
{
    return b.angleTo(VALUE);
}

Vector2 Vector2::Zero = Vector2();

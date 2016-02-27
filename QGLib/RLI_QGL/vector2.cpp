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

Vector2 Vector2::Zero = Vector2();

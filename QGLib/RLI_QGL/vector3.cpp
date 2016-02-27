#include "vector3.h"
#define VALUE (*this)

// Vector with a Mag of 1
Vector3 Vector3::normalized()
{
   return VALUE / mag();
}

// Magnitude of Vector
float Vector3::mag()
{
    return qSqrt( qPow(X,2)
                + qPow(Y,2)
                + qPow(Z,2));
}

// Addition Operators
Vector3  Vector3::operator +(const Vector3& other)
{
    return Vector3(this->X + other.X,
                   this->Y + other.Y,
                   this->Z + other.Z);
}
Vector3& Vector3::operator +=(const Vector3& other)
{
    VALUE = Vector3(this->X + other.X,
                    this->Y + other.Y,
                    this->Z + other.Z);
    return VALUE;
}

// Subtraction Operators
Vector3 operator -(const Vector3 self, const Vector3& other)
{
    return Vector3(self.X - other.X,
                   self.Y - other.Y,
                   self.Z - other.Z);
}
Vector3& Vector3::operator -=(const Vector3& other)
{                                                         // but often is, to modify the private members)
    VALUE = Vector3(this->X - other.X,
                    this->Y - other.Y,
                    this->Z - other.Z);
    return VALUE;
}

// Multiplication Operators
Vector3 operator *(const Vector3 self, const float& other)
{
    return Vector3(self.X * other,
                   self.Y * other,
                   self.Z * other);
}
Vector3& Vector3::operator *=(const float& other)
{
    VALUE = Vector3(this->X * other,
                    this->Y * other,
                    this->Z * other);
    return VALUE;
}

// Division Operators
Vector3 operator /(const Vector3 self, const float& other)
{
    return Vector3(self.X / other,
                   self.Y / other,
                   self.Z / other);
}
Vector3& Vector3::operator /=(const float& other)
{
    VALUE = Vector3(this->X / other,
                    this->Y / other,
                    this->Z / other);
    return VALUE;
}

Vector3 Vector3::Zero = Vector3();

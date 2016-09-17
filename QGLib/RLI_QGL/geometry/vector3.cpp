#include "vector3.h"

#include <string>
#include <sstream>
#include <QString>
#define VALUE (*this)

using namespace std;

namespace patch
{
    template < typename T > std::string toString( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

#include <iostream>

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
Vector3 Vector3::operator -(const Vector3& other)
{
    return Vector3(this->X - other.X,
                   this->Y - other.Y,
                   this->Z - other.Z);
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

Vector3 Vector3::cross(Vector3 b)
{
    return Vector3(this->Y*b.Z - this->Z*b.Y,
                   this->Z*b.X - this->X*b.Z,
                   this->X*b.Y - this->Y*b.X);
}

float Vector3::dot(Vector3 b)
{
    return this->X*b.X + this->Y*b.Y + this->Z*b.Z;
}

//Vector3 Vector3::rotate(const Vector3& angle){

//}

//Vector3 Vector3::rotate(const Quaternion& angle){

//}

Vector3 Vector3::Zero = Vector3();

QString Vector3::ToString()
{
    return QString::fromStdString(("Vector3("+patch::toString(X)+
                    ", " + patch::toString(Y) +
                    ", " + patch::toString(Z) + ")"));
}

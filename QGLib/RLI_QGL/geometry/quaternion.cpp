#include "quaternion.h"

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
} // NEEDS ITS OWN SPACE (UTILS?)

#include <iostream>

// FUNCTIONS HERE!!!!

Quaternion Quaternion::Identity = Quaternion();

QString Quaternion::ToString()
{
    return QString::fromStdString(("Quaternion(X:"+patch::toString(X)+
                                            ", Y:" + patch::toString(Y) +
                                            ", Z:" + patch::toString(Z) +
                                            ", W:" + patch::toString(W) + ")"));
}

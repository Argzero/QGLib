#include "plane.h"
#include "../utils/qglconstants.hpp"
#include <QDebug>

using namespace QGLConstants;

Plane::Plane(Vector3 p, Vector3 q, Vector3 r /*point_in_plane*/)
{
   Vector3 pq = q-p;
   Vector3 pr = r-p;
   normal = pq.cross(pr).normalized();
   d = normal.X*p.X + normal.Y*p.Y + normal.Z*p.Z;
   point = p;
}

void Plane::printEqn()
{
    if(SHOW_GEOMETRY_DEBUG) {
        qDebug() << "Equation of Plane: " << normal.X << "x"
                 << ((normal.Y>0)?"+":"-") << qAbs(normal.Y) << "y"
                 << ((normal.Z>0)?"+":"-") << qAbs(normal.Z) << "z = " << d;
    }
}

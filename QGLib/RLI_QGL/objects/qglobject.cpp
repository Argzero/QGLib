#include <QDebug>

#include "qglobject.h"
#include "shapes/qglshape.h"
#include "shapes/triangles/qgltriangle.h"
#include "shapes/quads/qglquad.h"
#include "shapes/polygons/qglpolygon.h"
#include "shapes/qglshape.h"
#include "text/qgltext.h"
#include "../qglconstants.hpp"

using namespace QGLConstants;

int QGLObject::countCreated = 0;

QGLObject::QGLObject(QGLObject::TYPE _type, QGLObject *_parent, Vector3 _pos, QGLObject::ALIGN _align)
{
    type = _type;
    parent = _parent;
    children = new QVector<QGLObject*>();
    position = _pos;
    alignment = _align;
    id = QGLObject::countCreated;
    QGLObject::countCreated += 1;
}

QGLObject::~QGLObject()
{
    QVector<QGLObject*> _obj_cpy = *children;
    while(_obj_cpy.size()>0){
        if(SHOW_DEBUG)
            qDebug("Killing Children...");
        TYPE t = _obj_cpy.first()->type;

        switch(t){
        case EMPTY:
            delete _obj_cpy.takeFirst();
            qDebug("Undefined QGLObject deleted.");
            break;
        case SHAPE:
            switch(static_cast<QGLShape*>(_obj_cpy.first())->shape)
            {
            case QGLShape::EMPTY:
                delete static_cast<QGLShape*>(_obj_cpy.takeFirst());
                if(SHOW_DEBUG)
                    qDebug("Deleted unspecified QGLShape.");
                break;
            case QGLShape::TRIANGLE:
                delete static_cast<QGLTriangle*>(_obj_cpy.takeFirst());
                if(SHOW_DEBUG)
                    qDebug("Triangle deleted.");
                break;
            case QGLShape::CIRCLE:
                delete _obj_cpy.takeFirst(); // TODO: CREATE CIRCLE AND MODIFY THIS!
                if(SHOW_DEBUG)
                    qDebug("WARNING: MEMORY LEAK, CIRCLE delete not defined!");
                break;
            case QGLShape::QUAD:
                delete static_cast<QGLQuad*>(_obj_cpy.takeFirst());
                if(SHOW_DEBUG)
                    qDebug("Rect deleted.");
                break;
            case QGLShape::POLYGON:
                delete static_cast<QGLPolygon*>(_obj_cpy.takeFirst());
                if(SHOW_DEBUG)
                    qDebug("Polygon deleted.");
                break;
            default:
                delete _obj_cpy.takeFirst();
                if(SHOW_DEBUG)
                    qDebug("WARNING: MEMORY LEAK, UNKNOWN_TYPE delete functionality unable to be determined!");
                break;
            }
            break;
        case TEXT:
            delete static_cast<QGLText*>(_obj_cpy.takeFirst());
            if(SHOW_DEBUG)
                qDebug() << "Text deleted.";
            break;
        default:
            delete _obj_cpy.takeFirst();
            if(SHOW_DEBUG)
                qDebug() << "Other QGLObject type deleted.";
            break;
        }
    }

    delete children;
    parent = NULL;
    window = NULL;
}

Vector3 QGLObject::GetPosition()
{
    return (parent!=NULL)? parent->GetPosition() + position: position;
}

void QGLObject::update()
{
    //qDebug() << children->length();
    for(int i = 0; i<children->length(); i++)
        children->at(i)->update();
}

void QGLObject::draw(QPainter *p)
{
    //qDebug() << children->length();
    for(int i = 0; i<children->length(); i++)
        children->at(i)->draw(p);
}

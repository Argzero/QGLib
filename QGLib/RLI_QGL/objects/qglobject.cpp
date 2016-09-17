#include <QDebug>

#include "qglobject.h"
#include "scenes/scenenode.h"
//#include "shapes/qglshape.h"
//#include "shapes/triangles/qgltriangle.h"
//#include "shapes/quads/qglquad.h"
//#include "shapes/surfaces/qglsurface.h"
//#include "shapes/qglshape.h"
#include "text/qgltext.h"
#include "../utils/qglconstants.hpp"
using namespace QGLConstants;

int QGLObject::countCreated = 0;

QGLObject::QGLObject(QGLObject::TYPE _type, QGLObject *_parent, Vector3 _pos, Vector3 _rot, Vector3 _scale, QGLObject::ALIGN _align, QGLObject::POSITIONING _posType)
{
    type = _type;
    parent = _parent;
    if(parent!=NULL){
        parent->children.push_back(this);
        window = parent->window;
    }
    position = _pos;
    rotation = _rot;
    scale = _scale;
    alignment = _align; // NEED TO MOVE THIS INTO AN INHERITABLE CLASS (IAlignable) : not all QGLObjects use this feature or even CAN use it
    positioning = _posType;
    enabled = true;
    id = QGLObject::countCreated;
    QGLObject::countCreated += 1;
    if(SHOW_CONSTRUCTION)
        qDebug("QGLObject Created!");
}

QGLObject::~QGLObject()
{
   if(SHOW_DESTRUCTION)
        qDebug("START ~QGLObject");
    while(children.size()>0){
        if(SHOW_DESTRUCTION)
            qDebug("Killing Children...");
        TYPE t = children.first()->type;

        switch(t){
        case EMPTY:
            delete children.takeFirst();
            if(SHOW_DESTRUCTION_WARNINGS)
                qDebug("Undefined QGLObject deleted.");
            break;
        /*case SHAPE:
            switch(static_cast<QGLShape*>(_obj_cpy.first())->shape)
            {
            case QGLShape::EMPTY:
                delete static_cast<QGLShape*>(_obj_cpy.takeFirst());
                if(SHOW_DESTRUCTION_WARNINGS)
                    qDebug("WARNING: Deleted unspecified QGLShape.");
                break;
            case QGLShape::TRIANGLE:
                delete static_cast<QGLTriangle*>(_obj_cpy.takeFirst());
                if(SHOW_DESTRUCTION)
                    qDebug("Triangle deleted.");
                break;
            case QGLShape::CIRCLE:
                delete _obj_cpy.takeFirst(); // TODO: CREATE CIRCLE AND MODIFY THIS!
                if(SHOW_DESTRUCTION_WARNINGS)
                    qDebug("WARNING: MEMORY LEAK, CIRCLE delete not defined!");
                break;
            case QGLShape::QUAD:
                delete static_cast<QGLQuad*>(_obj_cpy.takeFirst());
                if(SHOW_DESTRUCTION)
                    qDebug("Rect deleted.");
                break;
            case QGLShape::SURFACE:
                delete static_cast<QGLSurface*>(_obj_cpy.takeFirst());
                if(SHOW_DESTRUCTION)
                    qDebug("Surface/Polygon deleted.");
                break;
            default:
                delete _obj_cpy.takeFirst();
                if(SHOW_DESTRUCTION_WARNINGS)
                    qDebug("WARNING: MEMORY LEAK, UNKNOWN_TYPE delete functionality unable to be determined!");
                break;
            }
            break;*/
        case TEXT:
            delete dynamic_cast<QGLText*>(children.takeFirst());
            if(SHOW_DESTRUCTION)
                qDebug() << "Text deleted.";
            break;
        case SCENE:
            delete dynamic_cast<SceneNode*>(children.takeFirst());
            if(SHOW_DESTRUCTION)
                qDebug() << "Scene deleted.";
            break;
        default:
            delete children.takeFirst();
            if(SHOW_DESTRUCTION_WARNINGS)
                qDebug() << "WARNING: OTHER QGLObject type deleted.";
            break;
        }
    }

    parent = NULL;
    delete parent;
    window = NULL;
    delete window;

    if(SHOW_DESTRUCTION)
        qDebug("END ~QGLObject");
}

Vector3 QGLObject::GetPosition()
{
    return (parent!=NULL)? parent->GetPosition() + Vector3(position.X*parent->GetScale().X,
                                                           position.Y*parent->GetScale().Y,
                                                           position.Z*parent->GetScale().Z): position;
}

Vector3 QGLObject::GetScale()
{
    return (parent!=NULL)? Vector3(scale.X*parent->GetScale().X,
                                   scale.Y*parent->GetScale().Y,
                                   scale.Z*parent->GetScale().Z): scale;
}

Vector3 QGLObject::GetRotation()
{
    return (parent!=NULL)? Vector3(rotation.X*parent->GetScale().X,
                                   rotation.Y*parent->GetScale().Y,
                                   rotation.Z*parent->GetScale().Z): rotation;
}

void QGLObject::Update()
{
    qDebug() << "QGLObject BASE: " << children.length();
    for(int i = 0; i<children.length(); i++){
        children.at(i)->parent = this;
        children.at(i)->Update();
    }
}

void QGLObject::Draw(QPainter *p)
{
    //qDebug() << children->length();
    for(int i=0; i < children.length(); i++){
        // qDebug("QGLWINDOW OBJECT DRAW");
        if(children.at(i)->type==QGLObject::SCENE)
            continue;
        children.at(i)->Draw(p);
    }
    for(int i=0; i < children.length(); i++){
        // qDebug("QGLWINDOW SCENE DRAW");
        if(children.at(i)->type!=QGLObject::SCENE)
            continue;
        children.at(i)->Draw(p);
    }
}

void QGLObject::AddChild(QGLObject* _child)
{
    _child->parent = this;
    children.push_back(_child);
    children.last()->window = window;
}

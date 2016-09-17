#include <QDebug>

#include "scenenode.h"
#include "../../geometry/vector3.h"
#include "../../utils/qglconstants.hpp"

using namespace QGLConstants;

SceneNode::SceneNode(QOpenGLWidget* _window) : QGLObject(QGLObject::SCENE)
{
    window = _window;
    if(SHOW_CONSTRUCTION)
        qDebug("SceneNode Created.");
}

SceneNode::SceneNode(QGLObject* _parent,
                     Vector3 _pos,
                     Vector3 _rot,
                     Vector3 _scale,
                     QGLObject::ALIGN _align)
                     : QGLObject(QGLObject::SCENE, _parent, _pos, _rot, _scale, _align)
{
    window = _parent->window;

    if(SHOW_CONSTRUCTION)
        qDebug("SceneNode Created");
}


SceneNode::~SceneNode(){
    if(SHOW_DESTRUCTION){
        qDebug("~SceneNode");
    }
}

bool SceneNode::CheckClicked(){
    return false;
}
bool SceneNode::CheckMouseOver(QPainter* _p){
    return false;
}

void SceneNode::Update()
{
    //qDebug() << "SCENENODE UPDATE";
    QGLObject::Update();
}

void SceneNode::Draw(QPainter* p)
{
    //qDebug() << "SCENENODE DRAW";
    QGLObject::Draw(p);
}

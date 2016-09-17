 #ifndef SCENENODE_H
#define SCENENODE_H

#include "../qglobject.h"
#include "../special/iclickable.h"

class SceneNode : public QGLObject, public IClickable
{
public:
    SceneNode(QOpenGLWidget* _window);
    SceneNode(QGLObject* _parent, Vector3 _pos = Vector3::Zero, Vector3 _rot = Vector3(1,1,1),
              Vector3 _scale = Vector3(1,1,1), QGLObject::ALIGN _align= QGLObject::CENTER_MID);
    ~SceneNode();
    bool clicked;
    virtual void Update();
    virtual void Draw(QPainter *p);

    //MOUSE INTERACTIONS
    bool CheckClicked();
    bool CheckMouseOver(QPainter*);

};

#endif // SCENENODE_H

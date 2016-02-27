 #ifndef SCENENODE_H
#define SCENENODE_H

#include "../qglwindow.h"

class SceneNode : public QGLWindow
{
    Q_OBJECT
public:
    explicit SceneNode(QWidget *_parent = 0);
    ~SceneNode();
    void addComponents();
    void addBg(QColor c);
    void addBg(QVector<QColor> cVec);
signals:
public slots:
};

#endif // SCENENODE_H

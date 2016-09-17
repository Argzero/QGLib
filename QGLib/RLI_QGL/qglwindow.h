#ifndef QGLWINDOW_H
#define QGLWINDOW_H

#include <QOpenGLWidget>
#include <QFontDatabase>
#include <QPainter>
#include <QTimer>
#include <string>

#include "objects/scenes/scenenode.h"
#include "geometry/vector3.h"
#include "geometry/vector2.h"

class QGLWindow : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit QGLWindow(QWidget *parent = 0);
    virtual ~QGLWindow();
    QTimer* updateTimer;

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    // Convenience Functions
    void qglClearColor(QColor clearColor);
    void setBg(QVector<QColor> c);
    void clear(QPainter *p);
    void start();
    void updateCursor();

    // Scenes
    void AddScene(SceneNode* s);

    Vector2 GetMouse();
    void bgOff();
    void bgOn();

    //.........OBJECTS..&..SCENES..........//
    QVector<SceneNode*> scenes;
    Vector2 mouse;
    QVector<QColor> bgRectColors; //0-3 top-left, clockwise; 4 center.
    Vector2 bgCenterOffset;

private:
    bool bgON;

signals:

public slots:
    void updateGL();

};
#endif // QGLWINDOW_H
